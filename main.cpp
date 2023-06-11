#include "schedule.h"
#include "holidayCalendar.h"

int main()
{
    #if 0 // Set to 1 to test joint calendars

    std::shared_ptr<I_holidayCalendar> DKcal(new Calendar::DKCO());
    std::shared_ptr<I_holidayCalendar> T2(new Calendar::TARGET());

    // Create two joint calendars, one with inner joined holidays, one with outer joined.
    std::shared_ptr<I_holidayCalendar> inJoint(new Calendar::jointCalendar(DKcal, T2, true));
    std::shared_ptr<I_holidayCalendar> outJoint(new Calendar::jointCalendar(DKcal, T2));

    // Dates to test:
    finDate labourDay{ 2023, 5, 1 };    // this is target holiday, but not DK
    finDate christmas{ 2023, 12, 24};   // This is DK holiday, not target
    finDate firstJan{ 2023, 1, 1};      // This is DK holiday, and target
    finDate notHoliday{ 2023, 6, 12};    // This is not DK holiday, and not target

    std::cout << std::boolalpha;

    std::cout << "Labour day: (is only holiday in the Target calendar)\n";
    std::cout << "isHoliday with innerJoin (2023-05-01): " << inJoint->isHoliday(labourDay) << '\n';
    std::cout << "isHoliday with outerJoin (2023-05-01): " << outJoint->isHoliday(labourDay) << '\n';

    std::cout << "\nChristmas: (is only holiday in the DK calendar)\n";
    std::cout << "isHoliday with innerJoin (2023-12-24): " << inJoint->isHoliday(christmas) << '\n';
    std::cout << "isHoliday with outerJoin (2023-12-24): " << outJoint->isHoliday(christmas) << '\n';

    std::cout << "\nFirst of January: (is holiday in both DK and Target)\n";
    std::cout << "isHoliday with innerJoin (2023-01-01): " << inJoint->isHoliday(firstJan) << '\n';
    std::cout << "isHoliday with outerJoin (2023-01-01): " << outJoint->isHoliday(firstJan) << '\n';

    std::cout << '\n' << notHoliday << ": (is not holiday in either DK nor Target)\n";
    std::cout << "isHoliday with innerJoin (2023-01-01): " << inJoint->isHoliday(notHoliday) << '\n';
    std::cout << "isHoliday with outerJoin (2023-01-01): " << outJoint->isHoliday(notHoliday) << '\n';

    #endif

    /*
    schedule sched1{finDate(2023, 1, 6), finDate(2027, 1, 6), 4, 
                    std::unique_ptr<I_dayAdjustment>(new dayAdjustment::MF()),
                    std::unique_ptr<I_stub>(new stub::ShortFinal()),
                    std::shared_ptr<I_holidayCalendar>(new Calendar::jointCalendar(DKcal, T2)) };
*/
    return 0;
}