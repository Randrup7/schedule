#ifndef HYMAN_H
#define HYMAN_H

#include "I_interpolate.h"

namespace interpolate
{

class hyman : public I_interpolate
{
public:
    double operator()(std::vector<std::pair<finDate, double>>& coord, finDate outX) override final;
    ~hyman() = default;
};

}

#endif