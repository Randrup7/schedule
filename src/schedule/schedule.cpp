#include "schedule.h"
#include <algorithm>


schedule::schedule(finDate start, finDate maturity, interval freq, 
                    std::unique_ptr<I_dayAdjustment> dayrule, std::unique_ptr<I_stub> stubConvention,
                    std::shared_ptr<I_holidayCalendar> holidayCalendar) 
                    : m_start{ start }, m_maturity{ maturity}, m_freq{ freq }, 
                    m_dayRule{ std::move(dayrule) }, m_stubConvention{ std::move(stubConvention) },
                    m_holidayCalendar{ holidayCalendar }
{
    if (start >= maturity)
    {
        throw std::invalid_argument( "schedule Constructor: start date larger than maturity date." );
    }

    if (freq.isZero())
    {
        m_stubConvention = std::make_unique<stub::Zero>(stub::Zero());
    }

    calculateSchedule();
}

// Constructor with maturity as an interval (from start)
schedule::schedule(finDate start, interval maturity, interval freq, 
                    std::unique_ptr<I_dayAdjustment> dayrule, std::unique_ptr<I_stub> stubConvention,
                    std::shared_ptr<I_holidayCalendar> holidayCalendar) 
                    : m_start{ start }, m_freq{ freq }, 
                    m_dayRule{ std::move(dayrule) }, m_stubConvention{ std::move(stubConvention) },
                    m_holidayCalendar{ holidayCalendar }
{
    if (maturity.isZero())
    {
        throw std::invalid_argument( "schedule Constructor: maturity cannot be a zero interval." );
    }

    if (freq.isZero())
    {
        m_stubConvention = std::make_unique<stub::Zero>(stub::Zero());
    }

    m_maturity = start + maturity;

    calculateSchedule();
}

void schedule::calculateSchedule()
{
    m_stubConvention->fillSchedule(m_paymentDates, m_start, m_maturity, m_freq);

    for (finDate& date : m_paymentDates)
    {
        m_dayRule->adjustDate(date, m_holidayCalendar);
    }
}

///////////// Setter functions /////////////
void schedule::setFrequency(interval freq)
{
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


void schedule::printSchedule() const
{
    for (const finDate& date : m_paymentDates)
    {
        std::cout << date << '\n';
    }
}