#include "ACT360.h"

double dayCount::ACT360::operator()(const finDate& startDate, const finDate& endDate)
{
    return ((endDate - startDate) / 360.0);
}