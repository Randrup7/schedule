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
    interestRate(double rate, interval freq, compounding comp);

    double m_rate;
    compounding m_comp;
    interval m_freq;

    ~interestRate() = default;
};


double discountFactor(const interestRate& rate, double t);

double forwardRate(finDate anchor, finDate start, finDate maturity, 
                std::shared_ptr<I_dayCount> daycount, std::shared_ptr<I_dayAdjustment> dayAdjustment,
                std::shared_ptr<I_calendar> calendar, std::shared_ptr<I_interpolate> interpolate);


#endif