#include "schedule.h"


int main()
{   
    schedule sched1{finDate(2022, 7, 20), finDate(2027, 5, 20), 4, 
                    std::unique_ptr<I_dayAdjustment>(new dayAdjustment::MF()),
                    std::unique_ptr<I_stub>(new stub::LongFinal()) };

    return 0;
}