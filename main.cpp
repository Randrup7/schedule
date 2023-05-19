#include "schedule.h"
#include "holidayCalendar.h"

int main()
{
/*    schedule sched1{finDate(2022, 7, 20), finDate(2027, 5, 20), 4, 
                    std::unique_ptr<I_dayAdjustment>(new dayAdjustment::MF()),
                    std::unique_ptr<I_stub>(new stub::LongFinal()) };
*/

    finDate dato(2023,5,19);
    std::cout << dato.day_of_year() << '\n';

    std::cout << holidayFunctions::easterSunday(2016) << '\n';

    return 0;
}