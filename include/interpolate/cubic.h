#ifndef CUBIC_H
#define CUBIC_H

#include "I_interpolate.h"
#include <algorithm>    // std::upper_bound
#include <iterator>     // std::prev

namespace interpolate
{
enum class DerivativeMethod
{
    Hermite,
    FritschCarlson,
    FritschButland,
    Akima,
    Kruger,
    Harmonic,
    Parabolic,
    FourthOrder
};

enum class BoundaryCondition // Is this needed in these? ql doesnt use
{
    FirstDerivative, 
    SecondDerivative, // A second derivative equal to zero is also called 'natural spline'
    NotAKnot,
    Periodic,
    Quadratic
};

template <typename X, typename Y>
class cubic : public I_interpolate<X, Y>
{
private:
    DerivativeMethod m_derivativeMethod; // Estimation method for the first derivative
    BoundaryCondition m_leftCondition;   // Boundary condition for the left (low x values)
    BoundaryCondition m_rightCondition;  // Boundary condition for the right (dxigh x values)
    bool m_monotone;                     // if true, apply Hyman Monotonocity Filter (Hyman 1983)
    
    double m_leftValue;
    double m_rightValue;
public:
    cubic(DerivativeMethod derivativeMethod, bool monotone);
    Y operator()(const std::vector<std::pair<X, Y>>& coord, const X& outX) override final;
    ~cubic() = default;
};

}


template <typename X, typename Y>
interpolate::cubic<X, Y>::cubic(interpolate::DerivativeMethod derivativeMethod, bool monotone)
    : m_derivativeMethod{ derivativeMethod }, m_monotone{ monotone } {}


// Requirements for X and Y are:
//      X must support the less than "<" operator
//      X must support "-", "+" and return a double
template <typename X, typename Y>
Y interpolate::cubic<X, Y>::operator()(const std::vector<std::pair<X, Y>>& coord, const X& outX)
{
    typedef typename std::vector<const std::pair<X, Y>>::iterator iteratorType;

    // uBound is first iterator with first-value above outX using lambda function
    iteratorType uBound{ std::upper_bound(coord.begin(), coord.end(), outX, 
            [](const X& value, const std::pair<X, Y>& coord) { return value < coord.first; } ) };

    // lBound is iterator before uBound
    iteratorType lBound = std::prev(uBound, 1);

    // dist is distance from first pair to uBound
    typename std::iterator_traits<iteratorType>::difference_type dist{ std::distance(coord.begin(), uBound) };
    
    double tau = outX - lBound->first;                                  // distance from outX to lBound
    
    double dxi = uBound->first - lBound->first;                          // delta x_i (lenght between x-coordinates lBound and uBound)
    double dxh = lBound->first - std::prev(lBound, 1)->first;            // delta x_(i-1)
    double dxj = std::next(uBound, 1)->first - uBound->first;            // delta x_(i+1)
    
    double dyi = (uBound->second - lBound->second) / dxi;                 // delta y_i / delta x_i slope of y-coordinates between lBound and uBound (Hagan West 2006 equation 15)
    double dyh = (lBound->second - std::prev(lBound, 1)->second) / dxh;   // delta y_i-1 / delta x_i-1
    double dyj = (std::next(uBound, 1)->second - uBound->second) / dxj;   // delta y_i+1 / delta x_i+1
    
    double fDiffi;                                                        // Derivative at lBound knot
    double fDiffj;                                                        // Derivative at uBound knot


    if (dist == coord.size()) { return coord.back().second; }   // Flat extrapolation
    if (dist == 0) { return coord.front().second; }             // Flat extrapolation

    switch (m_derivativeMethod)
    {
    case DerivativeMethod::Hermite:
        // Implementing the cubic Hermite interpolation (Hagen West 2006 and de Boor 1978, 2001, Chapter IV Equation 9
        if (dist == 1) // when lbound - 1 doesn't exist
        {   
            // Equation 18
            fDiffi = ((dxi + dxi + dxj) * dyi - dxi * dyj) / (dxj + dxi);
            // fDiffi = (dxi * dyh + dxh * dyi) / (dxi + dxh);
            //                 dyj   (dxj + dxi + dxi)    dxj  <-- hvad dxh og dyh er ændret til

            // Equation 19
            fDiffj = (dxj * dyi + dxi * dyj) / (dxj + dxi);
        }
        else if (dist == coord.size() - 1) // when ubound + 1 doesn't exist
        {   
            // Equation 19 
            fDiffi = (dxi * dyh + dxh * dyi) / (dxi + dxh);

            // Equation 20
            fDiffj = ((dxi + dxi + dxh) * dyi - dxi * dyh) / (dxi + dxh);
        }
        else // uBound = j, lBound = i
        {
            // Equation 19
            fDiffi = (dxi * dyh + dxh * dyi) / (dxi + dxh);
            fDiffj = (dxj * dyi + dxi * dyj) / (dxj + dxi);
        }
        break; // Hermite end
    
    case DerivativeMethod::Akima:
        //if (/* dyi-2 = m_i-1 != dyi = dyi+1 */) // Do te same for fDiffj
        //{}
        //else
        {
        fDiffi = 0.0;

        fDiffj = 0.0;
        }
        

        break;
    case DerivativeMethod::FritschButland:
        break;
    case DerivativeMethod::FritschCarlson:
        break;
    case DerivativeMethod::Kruger:
        // Implementing the Kruger method from "Constrained Cubic Spline Interpolation" by CJC Kruger
        if (dist == 1)
        {
            if (dyi * dyj <= 0.0) { fDiffj = 0.0; }
            else { fDiffj = (2.0 * dyi * dyj) / (dyi + dyj); }
            
            fDiffi = (3.0 * dyi - fDiffj) / 2.0;
        } 
        else if (dist == coord.size() - 1) // when ubound + 1 doesn't exist
        {
            if (dyh * dyi <= 0.0) { fDiffi = 0.0; } // If slope changes, set fDiffi to 0
            else { fDiffi = (2.0 * dyh * dyi) / (dyh + dyi); }
            
            fDiffj = (3.0 * dyh - fDiffi) / 2.0;
        }
        else
        {
            if (dyh * dyi <= 0.0) { fDiffi = 0.0; } // If slope changes, set fDiffi to 0
            else { fDiffi = (2 * dyh * dyi) / (dyh + dyi); }

            if (dyi * dyj <= 0.0) { fDiffj = 0.0; }
            else { fDiffj = (2.0 * dyi * dyj) / (dyi + dyj); }
        }
        break; // Kruger end
    case DerivativeMethod::FourthOrder:
        break;
    case DerivativeMethod::Harmonic:
        break;
    case DerivativeMethod::Parabolic:
        break;
    default:
        break;
    }


    if (m_monotone) // Applying Hyman's monotonocity filter
    {
        // If slope sign for points before and around outX is different, set to zero to avoid extrema intra points
        if (dyh * dyi <= 0.0) { fDiffi = 0.0; }
        else
        {
            // Adjustment to f'(x_i), Hagen West 2006 equation 27 and Hyman 1983 Equation 2.3
            if (std::min(dyh, dyi) > 0.0) { fDiffi = std::min(std::max(0.0, fDiffi), 3.0 * std::min(dyh, dyi)); }
            if (std::max(dyh, dyi) < 0.0) { fDiffi = std::max(std::min(0.0, fDiffi), 3.0 * std::max(dyh, dyi)); }
        }
        // Same for fDiffj
        if (dyi * dyj <= 0.0) { fDiffj = 0.0; }
        else
        {
            if (std::min(dyi, dyj) > 0.0) { fDiffj = std::min(std::max(0.0, fDiffj), 3.0 * std::min(dyi, dyj)); }
            if (std::max(dyi, dyj) < 0.0) { fDiffj = std::max(std::min(0.0, fDiffj), 3.0 * std::max(dyi, dyj)); }
        }
    }

    double ai = lBound->second;
    double ci = (3.0 * dyi - fDiffj - 2.0 * fDiffi) / dxi;         // Hagan West 2006 equation 16
    double di = (fDiffj + fDiffi - 2.0 * dyi) / (dxi * dxi);      // Hagan West 2006 equation 17

    return ai + fDiffi * tau + ci * tau * tau + di * tau * tau * tau;
}

#endif