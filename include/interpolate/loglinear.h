#ifndef LOGLINEAR_H
#define LOGLINEAR_H

#include "I_interpolate.h"

namespace interpolate
{
class loglinear : public I_interpolate
{
public:
    double operator()(std::vector<std::pair<finDate, double>>& coord, finDate outX) override final;
    ~loglinear() = default;
};

}

#endif