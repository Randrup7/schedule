#include "loglinear.h"
#include <algorithm>    // std::upper_bound
#include <iterator>     // std::prev
#include <cmath>        // std::pow

double interpolate::loglinear::operator()(std::vector<std::pair<finDate, double>>& coord, finDate outX)
{
    using iteratorType = std::vector<std::pair<finDate, double>>::iterator;

    // uBound is first iterator with first-value above outX using lambda function
    iteratorType uBound{ std::upper_bound(coord.begin(), coord.end(), outX, 
            [](finDate value,  std::pair<finDate, double>& coord) { return value < coord.first; } ) };

    // lBound is iterator before uBound
    iteratorType lBound = std::prev(uBound, 1);
    double hi = uBound->first - lBound->first;              // lenght between x-coordinates lBound and uBound

    // dist is distance from first pair to uBound
    std::iterator_traits<iteratorType>::difference_type dist{ std::distance(coord.begin(), uBound) };

    if (dist == coord.size()) { return coord.back().second; }   // Flat extrapolation
    else if (dist == 0) { return coord.front().second; }        // Flat extrapolation

    else 
    {
        return std::pow(uBound->second, (outX - lBound->first) / hi) * 
                std::pow(lBound->second, (uBound->first - outX) / hi);         // Hagen West 2006 Equation 10
    }
}