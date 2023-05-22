#include "holidayCalendar.h"
#include <vector>

bool Calendar::DKCO::isHoliday(const finDate& date) const
{
    finDate easterDate = holidayFunctions::easterSunday(date.year()); 
    
    if ((date == finDate(date.year(), 1, 1))                        // 1. Januar
        || (date - easterDate == -3)                                // Skærtorsdag
        || (date - easterDate == -2)                                // Langfredag
        || (date - easterDate == 1)                                 // 2. påskedag
        || (date - easterDate == 39)                                // Kristi himmelfart 
        || (date - easterDate == 40)                                // Kristi himmelfart + 1
        || (date - easterDate == 50)                                // 2. pinsedag
        || (date == finDate(date.year(), 6, 5))                     // Grundlovsdag 
        || (date == finDate(date.year(), 12, 24))                   // Juleaften
        || (date == finDate(date.year(), 12, 25))                   // Juledag
        || (date == finDate(date.year(), 12, 26))                   // 2. Juledag
        || (date == finDate(date.year(), 12, 31))                   // Nytårsaften
        || ((date.year() <= 2023) && (date - easterDate == 26)))    // Store bededag
        { return true; }
    
    return false;
}





finDate holidayFunctions::easterSunday(int year)
{
    int a = year % 19;
    int b = year / 100;
    int c = year % 100;
    int d = b / 4;
    int e = b % 4;
    int f = (b + 8) / 24;
    int g = (b - f + 1) / 3;
    int h = (19 * a + b - d - g + 15) % 30;
    int i = c / 4;
    int k = c % 4;
    int l = (32 + 2 * e + 2 * i - h - k) % 7;
    int m = (a + 11 * h + 22 * l) / 451;

    int month = (h + l - 7 * m + 114) / 31;
    int day = (h + l - 7 * m + 114) % 31 + 1;

    return finDate(year, month, day);
}