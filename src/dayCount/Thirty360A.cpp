#include "Thirty360A.h"
#include <algorithm>

double dayCount::Thirty360A::operator()(const finDate& startDate, const finDate& endDate)
{
    unsigned int d1 = std::min<unsigned int>(30, startDate.day());
    unsigned int d2 = endDate.day();
    
    if (d2 == 31 && d1 > 29) { d2 = 30; }

    return ((endDate.year() - startDate.year()) * 360 + 
            (endDate.month() - startDate.month()) * 30 + 
            d2 - d1) / 360.0;
}