#ifndef INTERESTRATE_H
#define INTERESTRATE_H

#include <memory>
#include "dayCount/dayCount.h"
#include "time/interval.h"

enum class compounding
{
    Continuous,
    Discrete,
    Simple
};

class interestRate
{
private:
    double m_rate;
    interval m_freq;
    
    compounding m_comp;
public:
    interestRate(double rate, interval freq, compounding comp);

    double discountFactor(double t);

    ~interestRate() = default;
};

// Start by implementing a simple class
// then incorporate interpolate in a folder


#endif