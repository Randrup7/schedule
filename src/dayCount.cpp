#include "dayCount.h"

double DayCount::ACT360::operator()(finDate& startDate, finDate& endDate)
{
    return (endDate - startDate) / 360.0;
}
