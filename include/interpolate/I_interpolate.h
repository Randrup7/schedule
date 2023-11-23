#ifndef I_INTERPOLATE_H
#define I_INTERPOLATE_H

#include <vector>       // std::vector
#include <utility>      // std::pair
#include "../time/date.h"

// Base interface class for interpolate
template <typename X, typename Y>
class I_interpolate
{
public:
    virtual Y operator()(const std::vector<std::pair<X, Y>>& coord, const X& outX) = 0;
    virtual ~I_interpolate() = default;
};

double cubicSpline(double a, double b, double c, double d, double tau);

#endif