#include "hermite.h"
#include <cmath>        // std::pow
#include <algorithm>    // std::upper_bound
#include <iterator>     // std::prev

// Hermite interpolation with a vector of pairs
double interpolate::hermite::operator()(std::vector<std::pair<double, double>>& coord, double outX)
{
    using iteratorType = std::vector<std::pair<double, double>>::iterator;

    // uBound is first iterator with first-value above outX using lambda function
    iteratorType uBound{ std::upper_bound(coord.begin(), coord.end(), outX, 
            [](double value,  std::pair<double, double>& coord) { return value < coord.first; } ) };

    // lBound is iterator before uBound
    iteratorType lBound = std::prev(uBound, 1);

    // dist is distance from first pair to uBound
    std::iterator_traits<iteratorType>::difference_type dist{ std::distance(coord.begin(), uBound) };
            
    double bi;
    double bk;

    if (dist == coord.size()) { return coord.back().second; }   // Flat extrapolation
    else if (dist == 0) { return coord.front().second; }        // Flat extrapolation

    else if (dist == 1) // when lbound - 1 doesn't exist
    {   
            bi = ((std::next(uBound, 1)->first + uBound->first - 2 * lBound->first) * 
                    (uBound->second - lBound->second) /
                    (uBound->first - lBound->first) -
                    (uBound->first - lBound->first) *
                    (std::next(uBound, 1)->second - uBound->second) /
                    (std::next(uBound, 1)->first - uBound->first)) /
                    (std::next(uBound, 1)->first - lBound->first);  // Hagan West 2006 equation 18

            bk = ((std::next(uBound, 1)->first - uBound->first) *
                    (uBound->second - lBound->second) /
                    (uBound->first - lBound->first) +
                    (uBound->first - lBound->first) *
                    (std::next(uBound, 1)->second - uBound->second) /
                    (std::next(uBound, 1)->first - uBound->first)) /
                    (std::next(uBound, 1)->first - lBound->first);  // Hagan West 2006 equation 19
    }

    else if (dist == coord.size() - 1) // when ubound + 1 doesn't exist
    {        
            bi = ((uBound->first - lBound->first) * 
                    (lBound->second - std::prev(lBound, 1)->second) /
                    (lBound->first - std::prev(lBound, 1)->first) +
                    (lBound->first - std::prev(lBound, 1)->first) *
                    (uBound->second - lBound->second) /
                    (uBound->first - lBound->first)) /
                    (uBound->first - std::prev(lBound, 1)->first);  // Hagan West 2006 equation 19

            bk = -((uBound->first - lBound->first) * 
                    (lBound->second - std::prev(lBound, 1)->second) /
                    (lBound->first - std::prev(lBound, 1)->first) -
                    (2 * uBound->first - lBound->first - std::prev(lBound, 1)->first) * 
                    (uBound->second - lBound->second) /
                    (uBound->first - lBound->first)) /
                    (uBound->first - std::prev(lBound, 1)->first);  // Hagan West 2006 equation 20
    }

    else // uBound = k, lBound = i
    {
            bi = ((uBound->first - lBound->first) * 
                    (lBound->second - std::prev(lBound, 1)->second) /
                    (lBound->first - std::prev(lBound, 1)->first) +
                    (lBound->first - std::prev(lBound, 1)->first) *
                    (uBound->second - lBound->second) /
                    (uBound->first - lBound->first)) /
                    (uBound->first - std::prev(lBound, 1)->first);  // Hagan West 2006 equation 19

            bk = ((std::next(uBound, 1)->first - uBound->first) *
                    (uBound->second - lBound->second) /
                    (uBound->first - lBound->first) +
                    (uBound->first - lBound->first) *
                    (std::next(uBound, 1)->second - uBound->second) /
                    (std::next(uBound, 1)->first - uBound->first)) /
                    (std::next(uBound, 1)->first - lBound->first);  // Hagan West 2006 equation 19
    }

    double hi = uBound->first - lBound->first;           // lenght between x-coordinates lBound and uBound
    double mi = (uBound->second - lBound->second) / hi;  // Hagan West 2006 equation 15
    double ci = (3 * mi - bk - 2 * bi) / hi;             // Hagan West 2006 equation 16
    double di = (bk + bi - 2 * mi) * std::pow(hi, -2);   // Hagan West 2006 equation 17

    // this Bessel Hermite Cubic Spline may not preserve monotonicity between knot points. See Hyman filter for this.

    return cubicSpline(lBound->second, bi, ci, di, outX - lBound->first);
}