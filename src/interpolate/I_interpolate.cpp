#include "I_interpolate.h"
#include <cmath>        // std::pow

// This function returns the general formula of a cubicSpline. tau is within unit interval
double cubicSpline(double a, double b, double c, double d, double tau)
//double cubicSpline(double f0, double fDiff0, double f1, double fDiff1, double tau)
{
        // Considering a unit interval:
        //      a = f(0)
        //      b = f'(0)
        //      c = -3f(0) + 3f(1) - 2f'(0) - f'(1)
        //      d = 2f(0) - 2f(1) + f'(0) + f'(1)
        // return f0 + fDiff0 * tau +
        //            ((-3) * f0 + 3 * f1 - 2 * fDiff0 - fDiff1) * std::pow(tau, 2) +
        //            (2 * f0 - 2 * f1 + fDiff0 + fDiff1) * std::pow(tau, 3);
        return a + b * tau + c * std::pow(tau, 2) + d * std::pow(tau, 3);
}