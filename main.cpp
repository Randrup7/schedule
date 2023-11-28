#include "schedule.h"
#include "calendars.h"
#include "dayCount.h"
#include "interpolate.h"
#include "interestRate.h"
#include <iostream>
#include <typeinfo>

int main()
{
    std::shared_ptr<I_calendar> DKcal = std::make_shared<Calendar::DKCO>(Calendar::DKCO());
    std::shared_ptr<I_calendar> T2 = std::make_shared<Calendar::TARGET>(Calendar::TARGET());
    std::shared_ptr<I_calendar> outJoint = std::make_shared<Calendar::jointCalendar>(Calendar::jointCalendar(DKcal, T2));
    
    std::shared_ptr<dayCount::ACT360> daycount = std::make_shared<dayCount::ACT360>(dayCount::ACT360());
    std::shared_ptr<dayAdjustment::MF> dayAdj = std::make_shared<dayAdjustment::MF>(dayAdjustment::MF());
    std::shared_ptr<stub::ShortInitial> shortInitialStub = std::make_shared<stub::ShortInitial>(stub::ShortInitial());

    std::shared_ptr<I_interpolate<finDate, interestRate>> hermiteMono = std::make_shared<interpolate::cubic<finDate, interestRate>>(interpolate::DerivativeMethod::Hermite, false);

    std::vector<std::pair<finDate, interestRate>> curve{
        {finDate(2017,8,14), 0.008652},
        {finDate(2018,2,14), 0.012991},
        {finDate(2019,2,14), 0.018203},
        {finDate(2020,2,14), 0.025667},
        {finDate(2022,2,14), 0.025667},
        {finDate(2027,2,14), 0.018203},
    };

    #if 0 // Set to 1 to test joint calendars

    std::shared_ptr<I_calendar> inJoint = std::make_shared<Calendar::jointCalendar>(Calendar::jointCalendar(DKcal, T2, true));

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

    #if 0 // Testing interpolate

    interpolate::cubic<finDate, interestRate> hermite(interpolate::DerivativeMethod::Hermite, false);

    std::array<std::pair<finDate, interestRate>, 10> output;
    
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

    std::cout << "Kruger: \n";
    for (size_t i = 0; i < 10; i++)
    {
        output[i].second = hermiteMono(curve, output[i].first);
        std::cout << "x" << i << " = " << output[i].first << ", y" << i << " = " << output[i].second << '\n';
    }
    

    #endif


    double ann = annuity(finDate(2017,8,14), finDate(2017,8,14), finDate(2025,8,14), 3_M, curve, 
                    hermiteMono, daycount, dayAdj, shortInitialStub, outJoint);
    
    std::cout << ann << '\n';

    double floatPV = floatingPV(finDate(2017,8,14), finDate(2017,8,14), finDate(2025,8,14), 3_M, curve, curve, 
                                hermiteMono, daycount, dayAdj, shortInitialStub, outJoint);
    
    std::cout << floatPV << '\n';

    return 0;
}