#ifndef ACTACT_ISDA_H
#define ACTACT_ISDA_H

#include "I_dayCount.h"

namespace dayCount
{
class ACTACT_ISDA : public I_dayCount
{
    double operator()(const finDate& startDate, const finDate& endDate) override final;
    ~ACTACT_ISDA() = default;
};

}

#endif