#ifndef LINEAR_H
#define LINEAR_H

#include "I_interpolate.h"

namespace interpolate
{
class linear
{
public:
    double operator()(std::vector<std::pair<finDate, double>>& coord, finDate outX) override final;
    ~linear() = default;
};

}

#endif