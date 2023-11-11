#ifndef HERMITE_H
#define HERMITE_H

#include "I_interpolate.h"

namespace interpolate
{

class hermite : public I_interpolate
{
public:
    double operator()(std::vector<std::pair<double, double>>& coord, double outX) override final;
    ~hermite() = default;
};

}

#endif