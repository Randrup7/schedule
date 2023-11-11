#include "I_interpolate.h"
#include <cmath>        // std::pow

// This function returns the general formula of a cubicSpline. tau is within unit interval
double cubicSpline(double a, double b, double c, double d, double tau)
{
        return a + b * tau + c * std::pow(tau, 2) + d * std::pow(tau, 3);
}