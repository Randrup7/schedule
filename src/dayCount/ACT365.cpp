#include "ACT365.h"

double dayCount::ACT365::operator()(const finDate& startdate, const finDate& endDate)
{
    return (startdate - endDate) / 365.0;
}
