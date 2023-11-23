#ifndef LINEAR_H
#define LINEAR_H

#include "I_interpolate.h"
#include <algorithm>    // std::upper_bound
#include <iterator>     // std::prev

namespace interpolate
{
template <typename X, typename Y>
class linear : public I_interpolate<X, Y>
{
public:
    Y operator()(const std::vector<std::pair<X, Y>>& coord, const X& outX) override final;
    ~linear() = default;
};

}

template <typename X, typename Y>
Y interpolate::linear<X, Y>::operator()(const std::vector<std::pair<X, Y>>& coord, const X& outX)
{
    typedef typename std::vector<const std::pair<X, Y>>::iterator iteratorType;

    // uBound is first iterator with first-value above outX using lambda function
    iteratorType uBound{ std::upper_bound(coord.begin(), coord.end(), outX, 
            [](const X& value, const std::pair<X, Y>& coord) { return value < coord.first; } ) };

    // lBound is iterator before uBound
    iteratorType lBound = std::prev(uBound, 1);

    // dist is distance from first pair to uBound
    typename std::iterator_traits<iteratorType>::difference_type dist{ std::distance(coord.begin(), uBound) };

    if (dist == coord.size()) { return coord.back().second; }   // Flat extrapolation
    else if (dist == 0) { return coord.front().second; }        // Flat extrapolation

    else 
    {
        return ((uBound->first - outX) * lBound->second + (lBound->first - outX) * uBound->second) / (uBound->first - lBound->first); // linear
    }
}

#endif