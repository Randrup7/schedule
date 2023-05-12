#ifndef DAYCOUNT_H
#define DAYCOUNT_H

#include "date.h"

// Base interface class for dayCount
class I_dayCount
{
public:
    virtual double operator()(finDate& startDate, finDate& endDate) = 0;
    virtual ~I_dayCount(){};
};

namespace DayCount
{
// ACT/360 daycount class
class ACT360 : public I_dayCount
{
public:
    double operator()(finDate& startDate, finDate& endDate);
    virtual ~ACT360(){};
};

} // namespace DayCount


#endif