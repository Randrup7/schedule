#include "FRPA.h"

// Implementing the French calendar
bool Calendar::FRPA::isHoliday(const finDate& date) const
{
    int y = date.year();
    finDate easterDate = holidayFunctions::easterSunday(y); 
    
    if ((date == finDate(y, 1, 1))                      // 1. Januar
        || (date - easterDate == -2)                    // Langfredag
        || (date - easterDate == 1)                     // 2. påskedag
        || (date - easterDate == 39)                    // Kristi himmelfart 
        || (date - easterDate == 50)                    // 2. pinsedag
        || (date == finDate(y, 5, 1))                   // Labour Day 
        || (date == finDate(y, 5, 8))                   // Victory Day 
        || (date == finDate(y, 7, 14))                  // Nationaldag 
        || (date == finDate(y, 8, 15))                  // Assumption Day
        || (date == finDate(y, 11, 1))                  // All Saints Day 
        || (date == finDate(y, 11, 11))                 // Armistice Day 
        || (date == finDate(y, 12, 25))                 // Juledag
        || (date == finDate(y, 12, 26)))                // 2. Juledag
        { return true; }
    
    return false;
}