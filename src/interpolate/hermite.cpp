#include "hermite.h"
#include <cmath>        // std::pow
#include <algorithm>    // std::upper_bound
#include <iterator>     // std::prev

// Bessel (Hermite) Cubic Spline interpolation with a vector of pairs
double interpolate::hermite::operator()(std::vector<std::pair<finDate, double>>& coord, finDate outX)
{
        using iteratorType = std::vector<std::pair<finDate, double>>::iterator;

        // uBound is first iterator with first-value above outX using lambda function
        iteratorType uBound{ std::upper_bound(coord.begin(), coord.end(), outX, 
                [](finDate value,  std::pair<finDate, double>& coord) { return value < coord.first; } ) };

        // lBound is iterator before uBound
        iteratorType lBound = std::prev(uBound, 1);

        // dist is distance from first pair to uBound
        std::iterator_traits<iteratorType>::difference_type dist{ std::distance(coord.begin(), uBound) };
        
        double hi = uBound->first - lBound->first;              // lenght between x-coordinates lBound and uBound
        double mi = (uBound->second - lBound->second) / hi;     // slope of y-coordinates between lBound and uBound (Hagan West 2006 equation 15)
        double fDiff0;                                          // Derivative at lBound knot
        double fDiff1;                                          // Derivative at uBound knot

        if (dist == coord.size()) { return coord.back().second; }   // Flat extrapolation
        else if (dist == 0) { return coord.front().second; }        // Flat extrapolation

        else if (dist == 1) // when lbound - 1 doesn't exist
        {   
        iteratorType uBoundNext = std::next(uBound, 1);

        fDiff0 = ((uBoundNext->first + uBound->first - (lBound->first + lBound->first)) * mi -
                    hi * (uBoundNext->second - uBound->second) /
                    (uBoundNext->first - uBound->first)) /
                    (uBoundNext->first - lBound->first);  // Hagan West 2006 equation 18

        fDiff1 = ((uBoundNext->first - uBound->first) * mi +
                    hi * (uBoundNext->second - uBound->second) /
                    (uBoundNext->first - uBound->first)) /
                    (uBoundNext->first - lBound->first);  // Hagan West 2006 equation 19
        }

        else if (dist == coord.size() - 1) // when ubound + 1 doesn't exist
        {   
        iteratorType lBoundPrev = std::prev(lBound, 1);

        fDiff0 = (hi * (lBound->second - lBoundPrev->second) /
                    (lBound->first - lBoundPrev->first) +
                    (lBound->first - lBoundPrev->first) * mi) /
                    (uBound->first - lBoundPrev->first);  // Hagan West 2006 equation 19

        fDiff1 = -(hi * (lBound->second - lBoundPrev->second) /
                    (lBound->first - lBoundPrev->first) -
                    (uBound->first + uBound->first - (lBound->first + lBoundPrev->first)) * mi) /
                    (uBound->first - lBoundPrev->first);  // Hagan West 2006 equation 20
        }

        else // uBound = k, lBound = i
        {
        iteratorType uBoundNext = std::next(uBound, 1);
        iteratorType lBoundPrev = std::prev(lBound, 1);

        fDiff0 = (hi * (lBound->second - lBoundPrev->second) /
                    (lBound->first - lBoundPrev->first) +
                    (lBound->first - lBoundPrev->first) * mi) /
                    (uBound->first - lBoundPrev->first);  // Hagan West 2006 equation 19

        fDiff1 = ((uBoundNext->first - uBound->first) * mi +
                    hi * (uBoundNext->second - uBound->second) /
                    (uBoundNext->first - uBound->first)) /
                    (uBoundNext->first - lBound->first);  // Hagan West 2006 equation 19
        }

        double ci = (3 * mi - fDiff1 - 2 * fDiff0) / hi;                // Hagan West 2006 equation 16
        double di = (fDiff1 + fDiff0 - 2 * mi) * std::pow(hi, -2);      // Hagan West 2006 equation 17
        
        // this Bessel Hermite Cubic Spline may not preserve monotonicity between knot points. See Hyman filter for this.
        return cubicSpline(lBound->second, fDiff0, ci, di, outX - lBound->first);
}