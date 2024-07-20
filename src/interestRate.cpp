#include "interestRate.h"
#include "schedule.h"
#include <cmath>

interestRate::interestRate() : m_comp{ compounding::Continuous } {}

interestRate::interestRate(double rate, interval freq, compounding comp)
    : m_rate{ rate }, m_comp{ comp }
{
    if (freq.isZero())
    {
        throw std::invalid_argument( "interestRate Constructor: freq can not be a Zero interval." );
    }

    m_freq = freq;
}

interestRate::interestRate(double rate)
    : m_rate{ rate }
{
    m_comp = compounding::Continuous;
    m_freq = 1_Y;
}

double interestRate::operator-(const interestRate& rhs)       { return m_rate - rhs.m_rate; }
double interestRate::operator-(const interestRate& rhs) const { return m_rate - rhs.m_rate; }
double interestRate::operator+(const interestRate& rhs)       { return m_rate + rhs.m_rate; }
double interestRate::operator+(const interestRate& rhs) const { return m_rate + rhs.m_rate; }


double discountFactor(const interestRate& rate, double t)
{
    switch (rate.m_comp)
    {
    case compounding::Continuous:
        return std::exp(-rate.m_rate * t);
    
    case compounding::Discrete:
        return 1 / std::pow(1 + rate.m_rate / rate.m_freq.perYear(), rate.m_freq.perYear() * t);
    
    case compounding::Simple:
        return 1/ (1 - rate.m_rate * t);
    
    default:
        return -1.0;
    }
}

double discountFactor(const interestRate& rate, double t, compounding comp)
{
    switch (comp)
    {
    case compounding::Continuous:
        return std::exp(-rate.m_rate * t);
    
    case compounding::Discrete:
        return 1 / std::pow(1 + rate.m_rate / rate.m_freq.perYear(), rate.m_freq.perYear() * t);
    
    case compounding::Simple:
        return 1/ (1 - rate.m_rate * t);
    
    default:
        return -1.0;
    }
}

double forwardRate(const finDate& anchor, const finDate& start, const finDate& maturity, 
                    const std::vector<std::pair<finDate, interestRate>>& curve, 
                    std::shared_ptr<I_interpolate<finDate, interestRate>> interpolate,
                    std::shared_ptr<I_dayCount> daycount, std::shared_ptr<I_dayAdjustment> dayAdjustment)
{
    if (start >= maturity)
    {
        throw std::invalid_argument( "forwardRate: start date larger or equal to maturity date." );
    }
    if (anchor > start)
    {
        throw std::invalid_argument( "forwardRate: start date less than anchor date." );
    }

    // Assumption that compound convention is the same for all rates
    double ps = discountFactor(interpolate->operator()(curve, start), (start - anchor) / 365.0, curve[0].second.m_comp);
    double pe = discountFactor(interpolate->operator()(curve, maturity), (maturity - anchor) / 365.0, curve[0].second.m_comp);

    return (ps / pe - 1) / daycount->operator()(start, maturity);
}

double forwardRate(const finDate& anchor, const interval& start, const interval& maturity, 
                    const std::vector<std::pair<finDate, interestRate>>& curve, 
                    std::shared_ptr<I_interpolate<finDate, interestRate>> interpolate,
                    std::shared_ptr<I_dayCount> daycount, std::shared_ptr<I_dayAdjustment> dayAdjustment, 
                    std::shared_ptr<I_calendar> calendar)
{
    if (maturity.isZero())
    {
        throw std::invalid_argument( "forwardRate: maturity cannot be zero interval." );
    }

    finDate startDate = anchor + start;
    finDate maturityDate = startDate + maturity;

    dayAdjustment->adjustDate(startDate, calendar);
    dayAdjustment->adjustDate(maturityDate, calendar);

    return forwardRate(anchor, startDate, maturityDate, curve, interpolate, daycount, dayAdjustment);
}


double annuity(const finDate& anchor, const finDate& start, const finDate& maturity,
                const interval& freq, const std::vector<std::pair<finDate, interestRate>>& discCurve, 
                    std::shared_ptr<I_interpolate<finDate, interestRate>> interpolate,
                    std::shared_ptr<I_dayCount> daycount, std::shared_ptr<I_dayAdjustment> dayAdjustment,
                    std::shared_ptr<I_stub> stub, std::shared_ptr<I_calendar> Calendar)
{
    if (start >= maturity)
    {
        throw std::invalid_argument( "Annuity: start date larger or equal to maturity date." );
    }
    if (anchor > start)
    {
        throw std::invalid_argument( "Annuity: start date less than anchor date." );
    }
 
    schedule sched{start, maturity, freq, dayAdjustment, stub, Calendar};

    double annuity = 0;
    for (size_t i = 1; i < sched.m_paymentDates.size(); i++)
    {
        annuity += discountFactor(interpolate->operator()(discCurve, sched.m_paymentDates[i]), 
                    (sched.m_paymentDates[i] - anchor) / 365.0, discCurve[0].second.m_comp) * 
                    daycount->operator()(sched.m_paymentDates[i - 1], sched.m_paymentDates[i]);;
    }
    
    return annuity;
}

double annuity(const finDate& anchor, const interval& start, const interval& maturity,
                const interval& freq, const std::vector<std::pair<finDate, interestRate>>& discCurve, 
                    std::shared_ptr<I_interpolate<finDate, interestRate>> interpolate,
                    std::shared_ptr<I_dayCount> daycount, std::shared_ptr<I_dayAdjustment> dayAdjustment,
                    std::shared_ptr<I_stub> stub, std::shared_ptr<I_calendar> Calendar)
{
    if (maturity.isZero())
    {
        throw std::invalid_argument( "Annuity: maturity cannot be zero interval." );
    }

    finDate startDate = anchor + start;
    finDate maturityDate = startDate + maturity;
 
    return annuity(anchor, startDate, maturityDate, freq, discCurve, interpolate, daycount, dayAdjustment, stub, Calendar);
}

// Returns the value at anchor of receiving the floating rate from curve discounted with discCurve
double floatingPV(const finDate& anchor, const finDate& start, const finDate& maturity,
                const interval& freq, const std::vector<std::pair<finDate, interestRate>>& curve, 
                const std::vector<std::pair<finDate, interestRate>>& discCurve, 
                    std::shared_ptr<I_interpolate<finDate, interestRate>> interpolate,
                    std::shared_ptr<I_dayCount> daycount, std::shared_ptr<I_dayAdjustment> dayAdjustment,
                    std::shared_ptr<I_stub> stub, std::shared_ptr<I_calendar> Calendar)
{
    if (start >= maturity)
    {
        throw std::invalid_argument( "floatingPV: start date larger or equal to maturity date." );
    }
    if (anchor > start)
    {
        throw std::invalid_argument( "floatingPV: start date less than anchor date." );
    }

    schedule sched{start, maturity, freq, dayAdjustment, stub, Calendar};
    
    double PV = 0;
    for (size_t i = 1; i < sched.m_paymentDates.size(); i++)
    {
        PV += forwardRate(anchor, sched.m_paymentDates[i - 1], sched.m_paymentDates[i], curve, interpolate, daycount, dayAdjustment) *
                discountFactor(interpolate->operator()(discCurve, sched.m_paymentDates[i]), (sched.m_paymentDates[i] - anchor) / 365.0, discCurve[0].second.m_comp) * 
                daycount->operator()(sched.m_paymentDates[i - 1], sched.m_paymentDates[i]);;
    }
    
    return PV;
}

// Returns the value at anchor of receiving 1 unit annualy from start to maturity.
double annuity(const finDate& anchor, const interval& start, const interval& maturity,
                const interval& freq, const std::vector<std::pair<finDate, interestRate>>& discCurve, 
                    std::shared_ptr<I_interpolate<finDate, interestRate>> interpolate,
                    std::shared_ptr<I_dayCount> daycount, std::shared_ptr<I_dayAdjustment> dayAdjustment,
                    std::shared_ptr<I_stub> stub, std::shared_ptr<I_calendar> Calendar)
{
    if (maturity.isZero())
    {
        throw std::invalid_argument( "Annuity: maturity cannot be zero interval." );
    }

    finDate startDate = anchor + start;
    finDate maturityDate = startDate + maturity;
 
    return annuity(anchor, startDate, maturityDate, freq, discCurve, interpolate, daycount, dayAdjustment, stub, Calendar);
}



std::ostream& operator<<(std::ostream& out, const interestRate& rhs)
{
    out << rhs.m_rate;
    return out;
}