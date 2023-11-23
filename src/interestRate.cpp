#include "interestRate.h"
#include <cmath>

interestRate::interestRate(double rate, interval freq, compounding comp)
    : m_rate{ rate }, m_comp{ comp }
{
    if (freq.isZero())
    {
        throw std::invalid_argument( "interestRate Constructor: freq can not be a Zero interval." );
    }

    m_freq = freq;
}


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

double forwardRate(finDate anchor, finDate start, finDate maturity, 
                    std::vector<std::pair<finDate, double>> curve, std::shared_ptr<I_interpolate> interpolate)
    //std::shared_ptr<I_dayCount> daycount, std::shared_ptr<I_dayAdjustment> dayAdjustment,
    //std::shared_ptr<I_calendar> calendar, std::shared_ptr<I_interpolate> interpolate)
{
    if (start >= maturity)
    {
        throw std::invalid_argument( "forwardRate constructor: start date larger or equal to maturity date." );
    }
    if (anchor > start)
    {
        throw std::invalid_argument( "forwardRate constructor: start date less than anchor date." );
    }

    double ps = discountFactor()
}