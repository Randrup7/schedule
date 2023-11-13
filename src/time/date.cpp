#include "date.h"
#include <stdexcept>
#include <iomanip>
#include <numeric>
#include <iterator>

///////////// Constructors /////////////
finDate::finDate() : m_date{std::chrono::year{1970}, std::chrono::month{1}, std::chrono::day{1}} {}

finDate::finDate(int year, int month, int day) 
    : m_date{ std::chrono::year(year) / std::chrono::month(month) / std::chrono::day(day) }
{
    if (!m_date.ok())
    {
        throw std::invalid_argument( "finDate Constructor: Invalid date." );
    }
    resetSerialDate();
}

finDate::finDate(const ymd& date) : m_date{ date }
{
    if (!m_date.ok())
    {
        throw std::invalid_argument( "finDate Constructor: Invalid date." );
    }
    resetSerialDate();
}

///////////// Private member functions /////////////
void finDate::resetSerialDate()
{
    m_serialDate = std::chrono::sys_days(m_date).time_since_epoch().count();
}

///////////// Check state /////////////
int finDate::days_in_month() const
{
    int month = static_cast<unsigned int>(m_date.month());
    std::array<int, 12> normal_end_dates{ 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

    return (month != 2 || !m_date.year().is_leap() ? normal_end_dates[month - 1] : 29);
}

bool finDate::is_leap_year() const
{
    return m_date.year().is_leap();
}

int finDate::day_of_year() const
{
    std::array<int, 12> normal_end_dates{ 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
    unsigned int day_of_year = std::accumulate(normal_end_dates.begin(), std::next(normal_end_dates.begin(), this->month() - 1), 0);
    
    if (this->is_leap_year() && day_of_year >= (31 + 28)) { day_of_year = day_of_year + 1; }
    day_of_year = day_of_year + this->day();

    return day_of_year;
}

bool finDate::is_weekend() const
{
    std::chrono::weekday wd{ std::chrono::sys_days(m_date) };
    unsigned int day_of_week = wd.iso_encoding();
    return day_of_week > 5;
}

///////////// Arithmetic operations /////////////
finDate& finDate::addYears(int years)
{
    m_date += std::chrono::years(years);

    if (!m_date.ok()) { m_date = m_date.year() / m_date.month() / std::chrono::day(28); }

    resetSerialDate();
    return *this;
}

finDate& finDate::addMonths(int months)
{
    m_date += std::chrono::months(months);

    if (!m_date.ok()) { m_date = m_date.year() / m_date.month() / std::chrono::day(days_in_month()); }

    resetSerialDate();
    return *this;
}

finDate& finDate::addDays(int days)
{
    m_date = std::chrono::sys_days(m_date) + std::chrono::days(days);

    resetSerialDate();
    return *this;
}

///////////// Acessors /////////////
int finDate::year() const { return static_cast<int>(m_date.year()); }

int finDate::month() const { return static_cast<unsigned int>(m_date.month()); }

int finDate::day() const { return static_cast<unsigned int>(m_date.day()); }

int finDate::serialDate() const { return m_serialDate; }

const ymd finDate::year_month_day() const { return m_date; }

///////////// Operator overloading /////////////
int finDate::operator-(const finDate& rhs) { return m_serialDate - rhs.m_serialDate; }
int finDate::operator-(const finDate& rhs) const { return m_serialDate - rhs.m_serialDate; }
int finDate::operator+(const finDate& rhs) { return m_serialDate + rhs.m_serialDate; }
int finDate::operator+(const finDate& rhs) const { return m_serialDate + rhs.m_serialDate; }

bool finDate::operator==(const finDate& rhs) const { return m_serialDate == rhs.m_serialDate; }
bool finDate::operator>=(const finDate& rhs) const { return m_serialDate >= rhs.m_serialDate; }
bool finDate::operator<=(const finDate& rhs) const { return m_serialDate <= rhs.m_serialDate; }
bool finDate::operator>(const finDate& rhs) const { return m_serialDate > rhs.m_serialDate; }
bool finDate::operator<(const finDate& rhs) const { return m_serialDate < rhs.m_serialDate; }


finDate& finDate::operator-=(const interval& freq)
{
    switch (freq.m_timeUnit)
    {
    case timeUnit::Days:
        return addDays(-freq.m_lenght);
    
    case timeUnit::Weeks:
        return addDays(-(freq.m_lenght * 7));
    
    case timeUnit::Months:
        return addMonths(-freq.m_lenght);
    
    case timeUnit::Years:
        return addYears(-freq.m_lenght);

    default:
        return *this;
    }
}

finDate& finDate::operator+=(const interval& freq)
{
    switch (freq.m_timeUnit)
    {
    case timeUnit::Days:
        return addDays(freq.m_lenght);
    
    case timeUnit::Weeks:
        return addDays(freq.m_lenght * 7);
    
    case timeUnit::Months:
        return addMonths(freq.m_lenght);
    
    case timeUnit::Years:
        return addYears(freq.m_lenght);

    default:
        return *this;
    }
}

finDate operator+(const finDate& date, const interval& interval)
{
    finDate newDate = date;

    switch (interval.m_timeUnit)
    {
    case timeUnit::Days:
        return newDate.addDays(interval.m_lenght);
    
    case timeUnit::Weeks:
        return newDate.addDays(interval.m_lenght * 7);
    
    case timeUnit::Months:
        return newDate.addMonths(interval.m_lenght);
    
    case timeUnit::Years:
        return newDate.addYears(interval.m_lenght);

    default:
        return newDate;
    }    
}

finDate operator-(const finDate& date, const interval& interval)
{
    finDate newDate = date;

    switch (interval.m_timeUnit)
    {
    case timeUnit::Days:
        return newDate.addDays(-interval.m_lenght);
    
    case timeUnit::Weeks:
        return newDate.addDays(-(interval.m_lenght * 7));
    
    case timeUnit::Months:
        return newDate.addMonths(-interval.m_lenght);
    
    case timeUnit::Years:
        return newDate.addYears(-interval.m_lenght);

    default:
        return newDate;
    }    
}

std::ostream& operator<<(std::ostream& out, const finDate& rhs)
{
    out << rhs.year() << '-' << std::setw(2) << std::setfill('0') << rhs.month() << '-' 
        << std::setw(2) << std::setfill('0') << rhs.day();

    return out;
}