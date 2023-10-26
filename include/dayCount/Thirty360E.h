#ifndef Thirty360E_H
#define Thirty360E_H

#include "I_dayCount.h"

namespace dayCount
{

// 30E/360 daycount. 
// Also called 30/360 ICMA, 30/360 ISMA, 30S/360, Eurobond basis. As defined in ISDA 2006, Section 4.16(g)
class Thirty360E : public I_dayCount
{
public:
    double operator()(const finDate& startDate, const finDate& endDate) override final;
    ~Thirty360E() = default;
};

}

#endif