#ifndef ACT365_H
#define ACT365_H

#include "I_dayCount.h"

namespace dayCount
{
class ACT365 : public I_dayCount
{
    double operator()(const finDate& startDate, const finDate& endDate) override final;
    ~ACT365() = default;
};

}

#endif