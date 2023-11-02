#ifndef JOINTCALENDAR_H
#define JOINTCALENDAR_H

#include "I_calendar.h"
#include "../time/date.h"
#include <vector>


namespace Calendar
{
// A vector of calendars with either inner or outer join.
class jointCalendar : public I_calendar
{
private:
    std::vector<std::shared_ptr<I_calendar>> m_calendars;
    bool m_innerJoin;
public:
    jointCalendar(const std::shared_ptr<I_calendar> c1, const std::shared_ptr<I_calendar> c2, bool innerJoin = false);

    jointCalendar(const std::shared_ptr<I_calendar> c1, const std::shared_ptr<I_calendar> c2,
                  const std::shared_ptr<I_calendar> c3, bool innerJoin = false);

    jointCalendar(const std::shared_ptr<I_calendar> c1, const std::shared_ptr<I_calendar> c2,
                  const std::shared_ptr<I_calendar> c3, const std::shared_ptr<I_calendar> c4, bool innerJoin = false);

    jointCalendar(std::vector<std::shared_ptr<I_calendar>> calendars, bool innerJoin = false);

    bool isHoliday(const finDate& date) const override final;
    void addCalendar(const std::shared_ptr<I_calendar> newCalendar);

    virtual ~jointCalendar() = default;
};
}

#endif