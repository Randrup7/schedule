#ifndef INTERESTRATE_H
#define INTERESTRATE_H

#include "time/interval.h"
#include "time/date.h"
#include "dayCount/dayCount.h"
#include "schedule/dayAdjustment.h"
#include "calendars/calendars.h"
#include "interpolate/interpolate.h"
#include "schedule/stub.h"
#include <memory>

enum class compounding
{
    Continuous,
    Discrete,
    Simple
};

class interestRate
{
public:
    double m_rate;
    compounding m_comp;
    interval m_freq;

    interestRate();
    interestRate(double rate, interval freq, compounding comp);
    interestRate(double rate);

    double operator-(const interestRate& rhs);
    double operator-(const interestRate& rhs) const;
    double operator+(const interestRate& rhs);
    double operator+(const interestRate& rhs) const;

    friend std::ostream& operator<<(std::ostream& out, const interestRate& rhs);

    ~interestRate() = default;
};

double discountFactor(const interestRate& rate, double t);
double discountFactor(const interestRate& rate, double t, compounding comp);

// Calculate forward rate between start and maturity as per anchor
double forwardRate(const finDate& anchor, const finDate& start, const finDate& maturity, 
                    const std::vector<std::pair<finDate, interestRate>>& curve, 
                    std::shared_ptr<I_interpolate<finDate, interestRate>> interpolate,
                    std::shared_ptr<I_dayCount> daycount, std::shared_ptr<I_dayAdjustment> dayAdjustment);

// forward rate with interval as start and maturity input
double forwardRate(const finDate& anchor, const interval& start, const interval& maturity, 
                    const std::vector<std::pair<finDate, interestRate>>& curve, 
                    std::shared_ptr<I_interpolate<finDate, interestRate>> interpolate,
                    std::shared_ptr<I_dayCount> daycount, std::shared_ptr<I_dayAdjustment> dayAdjustment,
                    std::shared_ptr<I_calendar> Calendar);

// Calculate annuity between start and maturity as per anchor
double annuity(const finDate& anchor, const finDate& start, const finDate& maturity,
                const interval& freq, const std::vector<std::pair<finDate, interestRate>>& discCurve, 
                    std::shared_ptr<I_interpolate<finDate, interestRate>> interpolate,
                    std::shared_ptr<I_dayCount> daycount, std::shared_ptr<I_dayAdjustment> dayAdjustment,
                    std::shared_ptr<I_stub> stub, std::shared_ptr<I_calendar> Calendar);

// Annuity with interval as start and maturity input
double annuity(const finDate& anchor, const interval& start, const interval& maturity,
                const interval& freq, const std::vector<std::pair<finDate, interestRate>>& discCurve, 
                    std::shared_ptr<I_interpolate<finDate, interestRate>> interpolate,
                    std::shared_ptr<I_dayCount> daycount, std::shared_ptr<I_dayAdjustment> dayAdjustment,
                    std::shared_ptr<I_stub> stub, std::shared_ptr<I_calendar> Calendar);

double floatingPV(const finDate& anchor, const finDate& start, const finDate& maturity,
                const interval& freq, const std::vector<std::pair<finDate, interestRate>>& curve, 
                const std::vector<std::pair<finDate, interestRate>>& discCurve, 
                    std::shared_ptr<I_interpolate<finDate, interestRate>> interpolate,
                    std::shared_ptr<I_dayCount> daycount, std::shared_ptr<I_dayAdjustment> dayAdjustment,
                    std::shared_ptr<I_stub> stub, std::shared_ptr<I_calendar> Calendar);

double swapRate(const finDate& anchor, const interval& start, const interval& maturity,
                const interval& fixedFreq, const std::vector<std::pair<finDate, interestRate>>& discCurve, 
                    std::shared_ptr<I_interpolate<finDate, interestRate>> interpolate,
                    std::shared_ptr<I_dayCount> fixedDaycount, std::shared_ptr<I_dayAdjustment> dayAdjustment,
                    std::shared_ptr<I_stub> stub, std::shared_ptr<I_calendar> Calendar);

#endif