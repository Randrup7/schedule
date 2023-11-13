#include "hyman.h"
#include <cmath>        // std::pow
#include <algorithm>    // std::upper_bound
#include <iterator>     // std::prev

// generally results seem too low, check formulas
double interpolate::hyman::operator()(std::vector<std::pair<finDate, double>>& coord, finDate outX)
{
    using iteratorType = std::vector<std::pair<double, double>>::iterator;

    // uBound is first iterator with first-value above outX using lambda function
    iteratorType uBound{ std::upper_bound(coord.begin(), coord.end(), outX, 
    [](double value,  std::pair<double, double>& coord) { return value < coord.first; } ) };

    std::iterator_traits<iteratorType>::difference_type dist{ std::distance(coord.begin(), uBound) };

    if (dist == coord.size()) { return coord.back().second; }   // Flat extrapolation
    else if (dist == 0) { return coord.front().second; }        // Flat extrapolation

    // lBound is iterator before uBound
    iteratorType lBound = std::prev(uBound, 1);

    double hh = lBound->first - std::prev(lBound, 1)->first;
    double hi = uBound->first - lBound->first;
    double hk = std::next(uBound, 1)->first - uBound->first;

    double mh = (lBound->second - std::prev(lBound, 1)->second) / hh;
    double mi = (uBound->second - lBound->second) / hi;
    double mk = (std::next(uBound, 1)->second - uBound->second) / hk;

    double bi;
    double bk;
    
    if (dist == 1)
    {
            bi = 0.0; // Hagen West 2006 equation 25

            if (mi * mk < 0.0)
                    bk = 0.0;
            else
                    bk = (3.0 * mi * mk) / (std::max(mi, mk) + 2.0 * std::min(mi, mk)); // Hagen West 2006 equation 26
    }

    else if (dist == coord.size() - 1)
    {
            if (mh * mi < 0.0)
                    bi = 0.0;
            else
                    bi = (3.0 * mh * mi) / (std::max(mh, mi) + 2.0 * std::min(mh, mi)); // Hagen West 2006 equation 26

            bk = 0.0; // Hagen West 2006 equation 25
    }

    else
    {
            if (mh * mi < 0.0)
                    bi = 0.0;
            else
                    bi = (3.0 * mh * mi) / (std::max(mh, mi) + 2.0 * std::min(mh, mi)); // Hagen West 2006 equation 26

            if (mi * mk < 0.0)
                    bk = 0.0;
            else
                    bk = (3.0 * mi * mk) / (std::max(mi, mk) + 2.0 * std::min(mi, mk)); // Hagen West 2006 equation 26
    }

    // Adjustment to b, Hagen West 2006 equation 27
    // Make sure that the first below is sufficient to conlcude local decreasing monotonicity (second vice versa)
    if (mi < 0)
    {
            bi = std::max(std::min(0.0, bi), 3.0 * std::max(mh, mi));
            bk = std::max(std::min(0.0, bk), 3.0 * std::max(mi, mk));
    }
    if (mi > 0)
    {
            bi = std::min(std::max(0.0, bi), 3.0 * std::min(mh, mi));
            bk = std::min(std::max(0.0, bk), 3.0 * std::min(mi, mk));
    }

    double ci = (3 * mi - bk - 2 * bi) / hi;             // Hagan West 2006 equation 16
    double di = (bk + bi - 2 * mi) * std::pow(hi, -2);   // Hagan West 2006 equation 17

    return cubicSpline(lBound->second, bi, ci, di, outX - lBound->first);
}