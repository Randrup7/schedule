#include "holidayCalendar.h"
#include <vector>
#include <algorithm>

bool Calendar::DKCO::isHoliday(const finDate& date) const
{
    finDate easterDate = holidayFunctions::easterSunday(date.year());
    std::vector<finDate> holidays = { finDate(date.year(), 1, 1),       // 1. Januar
                                        easterDate.addDays(-3),         // Skærtorsdag
                                        easterDate.addDays(-2),         // Langfredag
                                        easterDate.addDays(1),          // 2. påskedag
                                        easterDate.addDays(39),         // 2. pinsedag 
                                        easterDate.addDays(40),         // 2. pinsedag 
                                        easterDate.addDays(50),         // 2. pinsedag
                                        finDate(date.year(), 6, 5),     // Grundlovsdag 
                                        finDate(date.year(), 12, 24),   // Juleaften
                                        finDate(date.year(), 12, 25),   // Juledag
                                        finDate(date.year(), 12, 26),   // 2. Juledag
                                        finDate(date.year(), 12, 31)    // Nytårsaften
                                        };
    if (date.year() <= 2023) { holidays.push_back(easterDate.addDays(26)); } // Store bededag

    return std::find(holidays.begin(), holidays.end(), date) != holidays.end();
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