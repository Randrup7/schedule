#include "ACT360_25.h"

double dayCount::ACT360_25::operator()(const finDate& startDate, const finDate& endDate)
{
    return ((endDate - startDate) / 360.25);
}