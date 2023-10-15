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
};


#endif