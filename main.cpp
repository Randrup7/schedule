#include "schedule.h"
#include "holidayCalendar.h"


int main()
{
    schedule sched1{finDate(2023, 1, 6), finDate(2027, 1, 6), 4, 
                    std::unique_ptr<I_dayAdjustment>(new dayAdjustment::MF()),
                    std::unique_ptr<I_stub>(new stub::ShortFinal()),
                    std::unique_ptr<I_holidayCalendar>(new Calendar::DKCO()) };

    return 0;
}