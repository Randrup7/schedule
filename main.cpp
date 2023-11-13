#include "schedule.h"
#include "calendars.h"
#include "dayCount.h"
#include "hermite.h"
#include <iostream>
#include <typeinfo>

int main()
{ //std::make_unique<stub::Zero>(stub::Zero());
    std::shared_ptr<I_calendar> DKcal = std::make_shared<Calendar::DKCO>(Calendar::DKCO());
    std::shared_ptr<I_calendar> T2 = std::make_shared<Calendar::TARGET>(Calendar::TARGET());

    // Create two joint calendars, one with inner joined holidays, one with outer joined.
    std::shared_ptr<I_calendar> inJoint = std::make_shared<Calendar::jointCalendar>(Calendar::jointCalendar(DKcal, T2, true));
    std::shared_ptr<I_calendar> outJoint = std::make_shared<Calendar::jointCalendar>(Calendar::jointCalendar(DKcal, T2));
    
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

    #if 0 // tester schedule
    schedule sched1{finDate(2023, 1, 6), 10_Y, 3_M, 
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

    #if 1 // Testing interpolate

    interpolate::hermite h{};

    std::vector<std::pair<finDate, double>> curve{
        {finDate(2022,1,1), 5.0},
        {finDate(2023,1,1), 2.0},
        {finDate(2024,1,1), 2.5},
        {finDate(2025,1,1), 5.0}
    };

    std::pair<finDate, double> out1;
    std::pair<finDate, double> out2;
    std::pair<finDate, double> out3;
    std::pair<finDate, double> out4;
    std::pair<finDate, double> out5;
    std::pair<finDate, double> out6;
    std::pair<finDate, double> out7;

    out1.first = finDate(2021, 12, 1);
    out2.first = finDate(2022, 1, 1);
    out3.first = finDate(2022, 7, 1);
    out4.first = finDate(2023, 7, 1);
    out5.first = finDate(2024, 7, 1);
    out6.first = finDate(2025, 1, 1);
    out7.first = finDate(2025, 2, 1);
    
    out1.second = h(curve, out1.first);
    out2.second = h(curve, out2.first);
    out3.second = h(curve, out3.first);
    out4.second = h(curve, out4.first);
    out5.second = h(curve, out5.first);
    out6.second = h(curve, out6.first);
    out7.second = h(curve, out7.first);

    std::cout << "Hermite: \n";
    std::cout << "x1 = " << out1.first << ", y1 = " << out1.second << '\n';
    std::cout << "x2 = " << out2.first << ", y2 = " << out2.second << '\n';
    std::cout << "x3 = " << out3.first << ", y3 = " << out3.second << '\n';
    std::cout << "x4 = " << out4.first << ", y4 = " << out4.second << '\n';
    std::cout << "x5 = " << out5.first << ", y5 = " << out5.second << '\n';
    std::cout << "x6 = " << out6.first << ", y6 = " << out6.second << '\n';
    std::cout << "x7 = " << out7.first << ", y7 = " << out7.second << '\n';

    #endif

    return 0;
}