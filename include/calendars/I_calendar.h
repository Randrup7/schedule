#ifndef I_CALENDAR_H
#define I_CALENDAR_H

#include "../time/date.h"
#include "holidayFunctions.h"

class I_calendar
{
public:
    virtual bool isHoliday(const finDate& date) const = 0;
    virtual ~I_calendar() = default;
};

#endif