#include "schedule.h"
#include "holidayCalendar.h"
#include "dayCount.h"
#include <iostream>

int main()
{
    std::shared_ptr<I_holidayCalendar> DKcal(new Calendar::DKCO());
    std::shared_ptr<I_holidayCalendar> T2(new Calendar::TARGET());

    // Create two joint calendars, one with inner joined holidays, one with outer joined.
    std::shared_ptr<I_holidayCalendar> inJoint(new Calendar::jointCalendar(DKcal, T2, true));
    std::shared_ptr<I_holidayCalendar> outJoint(new Calendar::jointCalendar(DKcal, T2));
    
    #if 0 // Set to 1 to test joint calendars

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

    #if 1 // tester schedule
    schedule sched1{finDate(2023, 1, 6), 10_Y, 0_D, 
                    std::make_unique<dayAdjustment::MF>(dayAdjustment::MF()),
                    std::make_unique<stub::ShortFinal>(stub::ShortFinal()),
                    std::make_shared<Calendar::jointCalendar>(Calendar::jointCalendar(DKcal, T2)) };
    
    sched1.printSchedule();

    #endif

    #if 0 // Tester daycount

    dayCount::ACT360 actual360{};

    finDate dag1{2023, 1, 6};
    finDate dag2{2024, 1, 6};

    std::cout << '\n';
    std::cout << "Difference between " << dag1 << " and " << dag2 << " using ACT/360 is: " << actual360(dag1, dag2) << '\n';
    
    #endif

    #if 0 // Tester interval

    interval Freq(3, timeUnit::Weeks);
    finDate today(2023, 10, 15);

    std::cout << today << '\n';
    today + Freq;
    std::cout << today << '\n';

    #endif

    return 0;
}