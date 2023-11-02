#include "jointCalendar.h"
#include <algorithm>

// Implementing Joint calendar constructors and isHoliday function
Calendar::jointCalendar::jointCalendar(const std::shared_ptr<I_calendar> c1, const std::shared_ptr<I_calendar> c2,
                    bool innerJoin) : m_innerJoin{ innerJoin }
{
    m_calendars.push_back(c1);
    m_calendars.push_back(c2);
}

Calendar::jointCalendar::jointCalendar(const std::shared_ptr<I_calendar> c1, const std::shared_ptr<I_calendar> c2,
                  const std::shared_ptr<I_calendar> c3, bool innerJoin) : m_innerJoin{ innerJoin }
{
    m_calendars.push_back(c1);
    m_calendars.push_back(c2);
    m_calendars.push_back(c3);
}

Calendar::jointCalendar::jointCalendar(const std::shared_ptr<I_calendar> c1, const std::shared_ptr<I_calendar> c2,
                  const std::shared_ptr<I_calendar> c3, const std::shared_ptr<I_calendar> c4, bool innerJoin) 
                  : m_innerJoin{ innerJoin }
{
    m_calendars.push_back(c1);
    m_calendars.push_back(c2);
    m_calendars.push_back(c3);
    m_calendars.push_back(c4);
}

Calendar::jointCalendar::jointCalendar(std::vector<std::shared_ptr<I_calendar>> calendars, bool innerJoin)
    : m_calendars{ calendars }, m_innerJoin{ innerJoin } {}

bool Calendar::jointCalendar::isHoliday(const finDate& date) const
{
    if (m_innerJoin)
    {
        return !(std::any_of(m_calendars.begin(), m_calendars.end(), 
            [&date](const std::shared_ptr<I_calendar>& cal){ return !(cal->isHoliday(date)); }
            ));            
    }
    else
        return std::any_of(m_calendars.begin(), m_calendars.end(), 
            [&date](const std::shared_ptr<I_calendar>& cal){ return cal->isHoliday(date); }
            );   
}

void Calendar::jointCalendar::addCalendar(const std::shared_ptr<I_calendar> newCalendar)
    { m_calendars.push_back(newCalendar); }