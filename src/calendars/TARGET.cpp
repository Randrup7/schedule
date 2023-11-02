#include "TARGET.h"

// Implementing TARGET calendar
bool Calendar::TARGET::isHoliday(const finDate& date) const
{
    int y = date.year();
    finDate easterDate = holidayFunctions::easterSunday(y);
    
    if ((date == finDate(y, 1, 1))                      // 1. Januar
        || (date - easterDate == -2 && (y >= 2000))     // Good Friday
        || (date - easterDate == 1 && (y >= 2000))      // Easter monday
        || (date == finDate(y, 5, 1) && (y >= 2000))    // Labour day 
        || (date == finDate(y, 12, 25))                 // Christmas
        || (date == finDate(y, 12, 26) && (y >= 2000))  // Day of Goodwill
        || (date == finDate(y, 12, 31) && 
            (y == 1998 || y == 1999 || y == 2001)))     // New years
        { return true; }
    
    return false;
}