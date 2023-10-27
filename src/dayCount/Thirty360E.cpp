#include "Thirty360E.h"
#include <algorithm>


double dayCount::Thirty360E::operator()(const finDate& startDate, const finDate& endDate)
{
    return ((endDate.year() - startDate.year()) * 360 + 
            (endDate.month() - startDate.month()) * 30 + 
            std::min<int>(30, endDate.day()) - std::min<int>(30,startDate.day())) / 360.0;
} 