#include "schedule.h"
#include "calendars.h"
#include "dayCount.h"
#include "interpolate.h"
#include <iostream>
#include <typeinfo>

int main()
{
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

    interpolate::cubic<finDate, double> hermite(interpolate::DerivativeMethod::Hermite, false);
    interpolate::cubic<finDate, double> hermiteMono(interpolate::DerivativeMethod::Kruger, false);

    std::vector<std::pair<finDate, double>> curve{
        {finDate(2017,8,14), 0.8652},
        {finDate(2018,2,14), 1.2991},
        {finDate(2019,2,14), 1.8203},
        {finDate(2020,2,14), 2.5667},
        {finDate(2022,2,14), 2.5667},
        {finDate(2027,2,14), 1.8203},
    };

    std::array<std::pair<finDate, double>, 10> output;
    
    output[0].first = finDate(2018, 2, 14);
    output[1].first = finDate(2019, 2, 14);
    output[2].first = finDate(2020, 2, 14);
    output[3].first = finDate(2021, 2, 14);
    output[4].first = finDate(2022, 2, 14);
    output[5].first = finDate(2023, 2, 14);
    output[6].first = finDate(2024, 2, 14);
    output[7].first = finDate(2025, 2, 14);
    output[8].first = finDate(2026, 2, 14);
    output[9].first = finDate(2027, 2, 14);
    
    std::cout << "Hermite: \n";
    for (size_t i = 0; i < 10; i++)
    {
        output[i].second = hermite(curve, output[i].first);
        std::cout << "x" << i << " = " << output[i].first << ", y" << i << " = " << output[i].second << '\n';
    }

    std::cout << "Hermite with Hyman: \n";
    for (size_t i = 0; i < 10; i++)
    {
        output[i].second = hermiteMono(curve, output[i].first);
        std::cout << "x" << i << " = " << output[i].first << ", y" << i << " = " << output[i].second << '\n';
    }

    #endif

    return 0;
}