#ifndef I_DAYCOUNT_H
#define I_DAYCOUNT_H

#include "../date.h"

// Base interface class for dayCount
class I_dayCount
{
public:
    virtual double operator()(const finDate& startDate, const finDate& endDate) = 0;
    virtual ~I_dayCount() = default;
};

#endif