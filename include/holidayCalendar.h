#ifndef HOLIDAYCALENDAR_H
#define HOLIDAYCALENDAR_H

#include "date.h"

class I_holidayCalendar
{
public:
    virtual bool isHoliday(const finDate& date) const = 0;
    virtual ~I_holidayCalendar() = default;
};

namespace Calendar
{
class DKCO : public I_holidayCalendar
{
public:
    bool isHoliday(const finDate& date) const override final;
    virtual ~DKCO() = default;
};

class noCalendar : public I_holidayCalendar
{
public:
    bool isHoliday(const finDate& date) const override final { return false; };
    virtual ~noCalendar() = default;
};


} // namespace Calendar


namespace holidayFunctions
{
    finDate easterSunday(int year);

} // namespace holidayFunctions

#endif