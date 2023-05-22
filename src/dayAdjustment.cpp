#include "dayAdjustment.h"

// adjustDate function for the modified following dayrule class
void dayAdjustment::MF::adjustDate(finDate& date, std::shared_ptr<I_holidayCalendar> calendar)
{
    std::chrono::weekday wd{ std::chrono::sys_days(date.year_month_day()) };
    std::chrono::month orig_month{ date.year_month_day().month() };

    unsigned int day_of_week{ wd.iso_encoding() };

    if (day_of_week > 5) { date.addDays(8 - day_of_week); } // If weekend; go forward

    while (calendar->isHoliday(date) || date.is_weekend()) // while the rolled-to date is not a business day
    {
        date.addDays(1);
    }

    if (orig_month < date.year_month_day().month()
        || (orig_month == std::chrono::December && date.year_month_day().month() == std::chrono::January)) 
    {
        while (calendar->isHoliday(date) || date.is_weekend()) // If we rolled to a new month, go back until day is valid.
        {
            date.addDays(-1);
        }
    }
}

// adjustDate function for the following dayrule class
void dayAdjustment::F::adjustDate(finDate& date, std::shared_ptr<I_holidayCalendar> calendar)
{
    std::chrono::weekday wd{ std::chrono::sys_days(date.year_month_day()) };

    unsigned int day_of_week{ wd.iso_encoding() }; // iso_encoding means sunday = 7

    if (day_of_week > 5) { date.addDays(8 - day_of_week); } // If weekend; go forward
    
    while (calendar->isHoliday(date) || date.is_weekend()) // while the rolled-to date is not a business day
    {
        date.addDays(1);
    }
}

// adjustDate function for the previous dayrule class
void dayAdjustment::P::adjustDate(finDate& date, std::shared_ptr<I_holidayCalendar> calendar)
{
    std::chrono::weekday wd{ std::chrono::sys_days(date.year_month_day()) };

    unsigned int day_of_week{ wd.iso_encoding() }; // iso_encoding means sunday = 7

    if (day_of_week > 5) { date.addDays(day_of_week - 5); } // If weekend; go back
    
    while (calendar->isHoliday(date) || date.is_weekend()) // while the rolled-to date is not a business day
    {
        date.addDays(-1);
    }
}