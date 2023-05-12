#include "schedule.h"
#include <algorithm>

schedule::schedule(finDate start, finDate maturity, unsigned int freq, 
                    std::unique_ptr<I_dayAdjustment> dayrule, std::unique_ptr<I_stub> stubConvention) 
                    : m_start{ start }, m_maturity{ maturity}, m_freq{ freq }, 
                    m_dayRule{ std::move(dayrule) }, m_stubConvention{ std::move(stubConvention) }
{
    if (start >= maturity)
    {
        throw std::invalid_argument( "schedule Constructor: start date larger than maturity date." );
    }
    
    if (freq != 1 && freq != 2 && freq != 4 && freq != 6 && freq != 12)
    {
        throw std::invalid_argument( "schedule Constructor: Invalid frequency. Must be 1, 2, 4, 6 or 12." );
    }

    calculateSchedule();
}

void schedule::calculateSchedule()
{
    m_stubConvention->fillSchedule(m_paymentDates, m_start, m_maturity, m_freq);

    for (finDate& date : m_paymentDates)
    {
        m_dayRule->adjustDate(date);
    }
}

///////////// Setter functions /////////////
void schedule::setFrequency(unsigned int freq)
{
    if (freq != 1 && freq != 2 && freq != 4 && freq != 6 && freq != 12)
    {
        throw std::invalid_argument( "Invalid frequency. Must be 1, 2, 4, 6 or 12." );
    }
    m_freq = freq;
    calculateSchedule();
}

void schedule::setStart(const finDate& start)
{
    if (start >= m_maturity)
    {
        throw std::invalid_argument( "Start date cannot be larger than maturity date." );
    }
    m_start = start;
    calculateSchedule();
}

void schedule::setMaturity(const finDate& maturity)
{
    if (maturity <= m_start)
    {
        throw std::invalid_argument( "Maturity date cannot be smaller than start date." );
    }

    m_maturity = maturity;
    calculateSchedule();
}

void schedule::setDayrule(std::unique_ptr<I_dayAdjustment> dayRule)
{
    m_dayRule = std::move(dayRule);
    calculateSchedule();
}

void schedule::setStubConvention(std::unique_ptr<I_stub> stubConvention)
{
    m_stubConvention = std::move(stubConvention);
    calculateSchedule();
}