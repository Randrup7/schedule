#ifndef NOCALENDAR_H
#define NOCALENDAR_H

#include "I_calendar.h"
#include "../time/date.h"

namespace Calendar
{
// A calendar with no holidays
class noCalendar : public I_calendar
{
public:
    bool isHoliday(const finDate& date) const override final { return false; };
    virtual ~noCalendar() = default;
};
}

#endif