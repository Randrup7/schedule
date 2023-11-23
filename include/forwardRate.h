#ifndef FORWARDRATE_H
#define FORWARDRATE_H

#include "time/date.h"
#include "dayCount/dayCount.h"
#include "schedule/dayAdjustment.h"
#include "interpolate/interpolate.h"

#include <memory>

class forwardRate
{
private:
    finDate m_anchor;
    finDate m_start;
    finDate m_maturity;

    std::shared_ptr<I_dayCount> m_daycount;
    std::shared_ptr<I_dayAdjustment> m_dayAdjustment;
    std::shared_ptr<I_calendar> m_calendar;
    std::shared_ptr<I_interpolate> m_interpolate;

public:
    forwardRate(finDate anchor, finDate start, finDate maturity, 
                std::shared_ptr<I_dayCount> daycount, std::shared_ptr<I_dayAdjustment> dayAdjustment,
                std::shared_ptr<I_calendar> calendar, std::shared_ptr<I_interpolate> interpolate);
    ~forwardRate() = default;
};


#endif