#include "ACTACT_ISDA.h"

double dayCount::ACTACT_ISDA::operator()(const finDate& startDate, const finDate& endDate)
{
    // if neither startdate or enddate is in leapyear and the difference between the dates is less than 4 years
    // then over 365
    
    
    return (startDate - endDate) / 365.0;
}
