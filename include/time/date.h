#ifndef DATE_H
#define DATE_H

#include <chrono>
#include <iostream>
#include <array>
#include <memory>
#include "interval.h"

using ymd = std::chrono::year_month_day;

class finDate
{
private:
    ymd m_date;
    int m_serialDate;

    void resetSerialDate();
public:
    // Constructors
    finDate();
    finDate(int year, int month, int day);
    finDate(const ymd& date);

    // Check state
    int days_in_month() const;
    bool is_leap_year() const;
    int day_of_year() const;
    bool is_weekend() const;

    // Arithmetic operations
    finDate& addYears(int years);
    finDate& addMonths(int months);
    finDate& addDays(int days);

    // Acessors
    int year() const;
    int month() const;
    int day() const;
    int serialDate() const;
    const ymd year_month_day() const;

    //// operators ////
    // Arithetic operators (used in interpolation amongst other things)
    int operator-(const finDate& rhs);
    int operator-(const finDate& rhs) const;
    int operator+(const finDate& rhs);
    int operator+(const finDate& rhs) const;

    finDate& operator-=(const interval& freq);
    finDate& operator+=(const interval& freq);
    
    bool operator==(const finDate& rhs) const;
    bool operator>=(const finDate& rhs) const;
    bool operator<=(const finDate& rhs) const;
    bool operator>(const finDate& rhs) const;
    bool operator<(const finDate& rhs) const;

    friend std::ostream& operator<<(std::ostream& out, const finDate& rhs);
};

finDate operator+(const finDate& date, const interval& interval);
finDate operator-(const finDate& date, const interval& interval);

#endif