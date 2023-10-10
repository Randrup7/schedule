#include "holidayCalendar.h"

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

// Implementing Joint calendar constructors and isHoliday function
Calendar::jointCalendar::jointCalendar(const std::shared_ptr<I_holidayCalendar> c1, const std::shared_ptr<I_holidayCalendar> c2,
                    bool innerJoin) : m_innerJoin{ innerJoin }
{
    m_calendars.push_back(c1);
    m_calendars.push_back(c2);
}

Calendar::jointCalendar::jointCalendar(const std::shared_ptr<I_holidayCalendar> c1, const std::shared_ptr<I_holidayCalendar> c2,
                  const std::shared_ptr<I_holidayCalendar> c3, bool innerJoin) : m_innerJoin{ innerJoin }
{
    m_calendars.push_back(c1);
    m_calendars.push_back(c2);
    m_calendars.push_back(c3);
}

Calendar::jointCalendar::jointCalendar(const std::shared_ptr<I_holidayCalendar> c1, const std::shared_ptr<I_holidayCalendar> c2,
                  const std::shared_ptr<I_holidayCalendar> c3, const std::shared_ptr<I_holidayCalendar> c4, bool innerJoin) 
                  : m_innerJoin{ innerJoin }
{
    m_calendars.push_back(c1);
    m_calendars.push_back(c2);
    m_calendars.push_back(c3);
    m_calendars.push_back(c4);
}

Calendar::jointCalendar::jointCalendar(std::vector<std::shared_ptr<I_holidayCalendar>> calendars, bool innerJoin)
    : m_calendars{ calendars }, m_innerJoin{ innerJoin } {}

bool Calendar::jointCalendar::isHoliday(const finDate& date) const
{
    if (m_innerJoin)
    {
        return !(std::any_of(m_calendars.begin(), m_calendars.end(), 
            [&date](const std::shared_ptr<I_holidayCalendar>& cal){ return !(cal->isHoliday(date)); }
            ));            
    }
    else
        return std::any_of(m_calendars.begin(), m_calendars.end(), 
            [&date](const std::shared_ptr<I_holidayCalendar>& cal){ return cal->isHoliday(date); }
            );   
}

void Calendar::jointCalendar::addCalendar(const std::shared_ptr<I_holidayCalendar> newCalendar)
    { m_calendars.push_back(newCalendar); }


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