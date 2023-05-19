#ifndef HOLIDAYCALENDAR_H
#define HOLIDAYCALENDAR_H

#include "date.h"

class I_holidayCalendar
{
private:
    /* data */
public:
    virtual ~I_holidayCalendar(){}
};


namespace holidayFunctions
{
    finDate easterSunday(int year);

} // namespace holidayFunctions

#endif