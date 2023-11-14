#include "interestRate.h"
#include <cmath>

interestRate::interestRate(double rate, interval freq, compounding comp)
    : m_rate{ rate }, m_comp{ comp }
{
    if (freq.isZero())
    {
        throw std::invalid_argument( "interestRate Constructor: freq can not be a Zero interval." );
    }

    m_freq = freq;
}


double interestRate::discountFactor(double t)
{
    switch (m_comp)
    {
    case compounding::Continuous:
        return std::exp(-m_rate * t);
    
    case compounding::Discrete:
        return 1 / std::pow(1 + m_rate / m_freq.perYear(), m_freq.perYear() * t);
    
    case compounding::Simple:
        return 1/ (1 - m_rate * t);
    
    default:
        return -1;
    }
}