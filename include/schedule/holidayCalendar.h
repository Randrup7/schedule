#ifndef HOLIDAYCALENDAR_H
#define HOLIDAYCALENDAR_H

#include "../date.h"
#include <algorithm>
#include <vector>

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
public:
    bool isHoliday(const finDate& date) const override final;
    virtual ~DKCO() = default;
};

class TARGET : public I_holidayCalendar
{
public:
    bool isHoliday(const finDate& date) const override final;
    virtual ~TARGET() = default;
};

class jointCalendar : public I_holidayCalendar
{
private:
    std::vector<std::shared_ptr<I_holidayCalendar>> m_calendars;
    bool m_innerJoin;
public:
    jointCalendar(const std::shared_ptr<I_holidayCalendar> c1, const std::shared_ptr<I_holidayCalendar> c2, bool innerJoin = false);

    jointCalendar(const std::shared_ptr<I_holidayCalendar> c1, const std::shared_ptr<I_holidayCalendar> c2,
                  const std::shared_ptr<I_holidayCalendar> c3, bool innerJoin = false);

    jointCalendar(const std::shared_ptr<I_holidayCalendar> c1, const std::shared_ptr<I_holidayCalendar> c2,
                  const std::shared_ptr<I_holidayCalendar> c3, const std::shared_ptr<I_holidayCalendar> c4, bool innerJoin = false);

    jointCalendar(std::vector<std::shared_ptr<I_holidayCalendar>> calendars, bool innerJoin = false);

    bool isHoliday(const finDate& date) const override final;
    void addCalendar(const std::shared_ptr<I_holidayCalendar> newCalendar);

    virtual ~jointCalendar() = default;
};

class noCalendar : public I_holidayCalendar
{
public:
    bool isHoliday(const finDate& date) const override final { return false; };
    virtual ~noCalendar() = default;
};


} // namespace Calendar


namespace holidayFunctions
{
    finDate easterSunday(int year);

} // namespace holidayFunctions

#endif