#ifndef INTERVAL_H
#define INTERVAL_H

// Most important consideration is the overloading, meaning it should be a type
//      How should that handle the zero cpn
//      How would a businessDay timeUnit work?
//      check out literals to make it possible to enter 3M, 2Y etc.
//      Make other checks

enum class timeUnit
{
    Zero,
    Days,
    Weeks,
    Months,
    Years
};

class interval
{
public:
    unsigned int m_lenght;
    timeUnit m_timeUnit;
    interval(unsigned int lenght = 0, timeUnit timeunit = timeUnit::Zero);
    double perYear();

    bool isZero();
};


// User defined Literals for intervals
interval operator ""_D(unsigned long long int D);
interval operator ""_W(unsigned long long int W);
interval operator ""_M(unsigned long long int M);
interval operator ""_Y(unsigned long long int Y);

#endif