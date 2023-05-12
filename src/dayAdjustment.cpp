#include "dayAdjustment.h"

// adjustDate function for the modified following dayrule class
void dayAdjustment::MF::adjustDate(finDate& date)
{
    std::chrono::weekday wd{ std::chrono::sys_days(date.year_month_day()) };
    std::chrono::month orig_month{ date.year_month_day().month() };

    unsigned int day_of_week{ wd.iso_encoding() };

    if (day_of_week > 5)
    {
        date.addDays(8 - day_of_week);
    }

    if (orig_month < date.year_month_day().month()
        || (orig_month == std::chrono::December && date.year_month_day().month() == std::chrono::January))
    {
        date.addDays(3);
    }
}

// adjustDate function for the following dayrule class
void dayAdjustment::F::adjustDate(finDate& date)
{
    std::chrono::weekday wd{ std::chrono::sys_days(date.year_month_day()) };

    unsigned int day_of_week{ wd.iso_encoding() };

    if (day_of_week > 5)
    {
        date.addDays(8 - day_of_week);
    }
}

// adjustDate function for the previous dayrule class
void dayAdjustment::P::adjustDate(finDate& date)
{
    std::chrono::weekday wd{ std::chrono::sys_days(date.year_month_day()) };

    unsigned int day_of_week{ wd.iso_encoding() };

    if (day_of_week > 5) { date.addDays(day_of_week - 5); }
}