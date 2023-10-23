#include "ACT365.h"

double dayCount::ACT365::operator()(const finDate& startDate, const finDate& endDate)
{
    return (startDate - endDate) / 365.0;
}
