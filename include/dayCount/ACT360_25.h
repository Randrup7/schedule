#ifndef ACT360_25_H
#define ACT360_25_H

#include "I_dayCount.h"

namespace dayCount
{

// ACT/360 daycount class
class ACT360_25 : public I_dayCount
{
public:
    double operator()(const finDate& startDate, const finDate& endDate) override final;
    ~ACT360_25() = default;
};

}

#endif