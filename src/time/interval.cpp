#include "interval.h"

interval::interval(unsigned int lenght, timeUnit timeunit)
    : m_lenght{ lenght }, m_timeUnit{ timeunit } {}

bool interval::isZero()
{
    return (m_lenght == 0 || m_timeUnit == timeUnit::Zero);
}

// User defined Literals for intervals
interval operator ""_D(unsigned long long int D) { return interval(D, timeUnit::Days); }
interval operator ""_W(unsigned long long int W) { return interval(W, timeUnit::Weeks); }
interval operator ""_M(unsigned long long int M) { return interval(M, timeUnit::Months); }
interval operator ""_Y(unsigned long long int Y) { return interval(Y, timeUnit::Years); }