#ifndef INTERESTRATE_H
#define INTERESTRATE_H

#include "time/interval.h"
#include "time/date.h"
#include "dayCount/dayCount.h"
#include "schedule/dayAdjustment.h"
#include "calendars/calendars.h"
#include "interpolate/interpolate.h"
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

double forwardRate(const finDate& anchor, const finDate& start, const finDate& maturity, 
                    const std::vector<std::pair<finDate, interestRate>>& curve, 
                    std::shared_ptr<I_interpolate<finDate, interestRate>> interpolate,
                    std::shared_ptr<I_dayCount> daycount); //, std::shared_ptr<I_dayAdjustment> dayAdjustment);


#endif