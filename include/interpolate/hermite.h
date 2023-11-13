#ifndef HERMITE_H
#define HERMITE_H

#include "I_interpolate.h"

namespace interpolate
{

class hermite : public I_interpolate
{
public:
    double operator()(std::vector<std::pair<finDate, double>>& coord, finDate outX) override final;
    ~hermite() = default;
};

}

#endif