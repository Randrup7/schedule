#ifndef Thirty360A_H
#define Thirty360A_H

#include "I_dayCount.h"

namespace dayCount
{

// 30A/360 daycount. 
// Also called 30/360 Bond Basis. As defined in ISDA 2006, Section 4.16(f)
class Thirty360A : public I_dayCount
{
public:
    double operator()(const finDate& startDate, const finDate& endDate) override final;
    ~Thirty360A() = default;
};

}

#endif