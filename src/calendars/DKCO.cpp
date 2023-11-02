#include "DKCO.h"

// Implementing the Danish calendar
bool Calendar::DKCO::isHoliday(const finDate& date) const
{
    int y = date.year();
    finDate easterDate = holidayFunctions::easterSunday(y); 
    
    if ((date == finDate(y, 1, 1))                      // 1. Januar
        || (date - easterDate == -3)                    // Skærtorsdag
        || (date - easterDate == -2)                    // Langfredag
        || (date - easterDate == 1)                     // 2. påskedag
        || (date - easterDate == 39)                    // Kristi himmelfart 
        || (date - easterDate == 40)                    // Kristi himmelfart + 1
        || (date - easterDate == 50)                    // 2. pinsedag
        || (date == finDate(y, 6, 5))                   // Grundlovsdag 
        || (date == finDate(y, 12, 24))                 // Juleaften
        || (date == finDate(y, 12, 25))                 // Juledag
        || (date == finDate(y, 12, 26))                 // 2. Juledag
        || (date == finDate(y, 12, 31))                 // Nytårsaften
        || ((y <= 2023) && (date - easterDate == 26)))  // Store bededag
        { return true; }
    
    return false;
}