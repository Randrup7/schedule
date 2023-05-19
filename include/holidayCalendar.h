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
private:
    /* data */
public:
    bool isHoliday(const finDate& date) const override final;
    virtual ~DKCO() = default;
};



} // namespace Calendar


namespace holidayFunctions
{
    finDate easterSunday(int year);

} // namespace holidayFunctions

#endif