#ifndef I_INTERPOLATE_H
#define I_INTERPOLATE_H

#include <vector>       // std::vector
#include <utility>      // std::pair

// Base interface class for interpolate
class I_interpolate
{
public:
    virtual double operator()(std::vector<std::pair<double, double>>& coord, double outX) = 0;
    virtual ~I_interpolate() = default;
};

double cubicSpline(double a, double b, double c, double d, double tau);

#endif