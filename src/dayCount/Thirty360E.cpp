#include "Thirty360E.h"

double dayCount::Thirty360E::operator()(const finDate& startDate, const finDate& endDate)
{
    return ((startDate.year() - endDate.year()) * 360 + 
            (startDate.month() - endDate.month()) * 30 + 
            startDate.day() - endDate.day()) / 360.0;
}