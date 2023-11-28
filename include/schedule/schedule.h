#ifndef SCHEDULE_H
#define SCHEDULE_H

#include <vector>
#include <memory>
#include "dayAdjustment.h"
#include "stub.h"

class schedule
{
public:
    std::vector<finDate> m_paymentDates;
private:
    finDate m_start; 
    finDate m_maturity;
    interval m_freq;

    std::shared_ptr<I_dayAdjustment> m_dayRule;
    std::shared_ptr<I_stub> m_stubConvention;
    std::shared_ptr<I_calendar> m_holidayCalendar;

    finDate m_first; // First regular cpn date, how to handle Zero Cpns
    finDate m_secondToLast; // last regular cpn date, how to handle Zero Cpns    

    void calculateSchedule();

public:
    // Constructors
    schedule(const finDate& start, const finDate& maturity, const interval& freq, 
            std::shared_ptr<I_dayAdjustment> dayRule, std::shared_ptr<I_stub> stubConvention, 
            std::shared_ptr<I_calendar> m_holidayCalendar = std::make_shared<Calendar::noCalendar>(Calendar::noCalendar())); 

    schedule(finDate start, interval maturity, interval freq, 
            std::shared_ptr<I_dayAdjustment> dayRule, std::shared_ptr<I_stub> stubConvention, 
            std::shared_ptr<I_calendar> m_holidayCalendar = std::make_shared<Calendar::noCalendar>(Calendar::noCalendar())); 

    void setFrequency(interval freq);
    void setStart(const finDate& start);
    void setMaturity(const finDate& maturity);
    void setDayrule(std::shared_ptr<I_dayAdjustment> dayRule);
    void setStubConvention(std::shared_ptr<I_stub> stubConvention);

    void printSchedule() const;

    // Next date const / non-const and return type?
    // Previous date

};

#endif