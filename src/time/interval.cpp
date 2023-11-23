#include "interval.h"

interval::interval(unsigned int lenght, timeUnit timeunit)
    : m_lenght{ lenght }, m_timeUnit{ timeunit } {}

bool interval::isZero()
{
    return (m_lenght == 0 || m_timeUnit == timeUnit::Zero);
}

double interval::perYear()
{
    switch (m_timeUnit)
    {
    case timeUnit::Days:
        return 365 / m_lenght; 

    case timeUnit::Weeks:
        return 365 / 52;
    
    case timeUnit::Months:
        return 12 / m_lenght;
    
    case timeUnit::Years:
        return 1 / m_lenght;
    
    case timeUnit::Zero:
        return 0;
    default:
        return 0;
    }
}

const double interval::perYear() const
{
    switch (m_timeUnit)
    {
    case timeUnit::Days:
        return 365 / m_lenght; 

    case timeUnit::Weeks:
        return 365 / 52;
    
    case timeUnit::Months:
        return 12 / m_lenght;
    
    case timeUnit::Years:
        return 1 / m_lenght;
    
    case timeUnit::Zero:
        return 0;
    default:
        return 0;
    }
}

// User defined Literals for intervals
interval operator ""_D(unsigned long long int D) { return interval(D, timeUnit::Days); }
interval operator ""_W(unsigned long long int W) { return interval(W, timeUnit::Weeks); }
interval operator ""_M(unsigned long long int M) { return interval(M, timeUnit::Months); }
interval operator ""_Y(unsigned long long int Y) { return interval(Y, timeUnit::Years); }