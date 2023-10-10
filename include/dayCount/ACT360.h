#ifndef ACT360_H
#define ACT360_H

#include "I_dayCount.h"

namespace dayCount
{

// ACT/360 daycount class
class ACT360 : public I_dayCount
{
public:
    double operator()(const finDate& startDate, const finDate& endDate) override final;
    ~ACT360() = default;
};

}

#endif