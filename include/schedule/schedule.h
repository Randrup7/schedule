#ifndef SCHEDULE_H
#define SCHEDULE_H

#include <vector>
#include "dayAdjustment.h"
#include "stub.h"

class schedule
{
private:
    finDate m_start; 
    finDate m_maturity;
    interval m_freq;
    std::unique_ptr<I_dayAdjustment> m_dayRule;
    std::unique_ptr<I_stub> m_stubConvention;
    std::shared_ptr<I_holidayCalendar> m_holidayCalendar;
    
    std::vector<finDate> m_paymentDates;

    void calculateSchedule();

public:
    // Constructors
    schedule(finDate start, finDate maturity, interval freq, 
            std::unique_ptr<I_dayAdjustment> dayRule, std::unique_ptr<I_stub> stubConvention, 
            std::shared_ptr<I_holidayCalendar> m_holidayCalendar = std::shared_ptr<I_holidayCalendar>(new Calendar::noCalendar())); 

    schedule(finDate start, interval maturity, interval freq, 
            std::unique_ptr<I_dayAdjustment> dayRule, std::unique_ptr<I_stub> stubConvention, 
            std::shared_ptr<I_holidayCalendar> m_holidayCalendar = std::shared_ptr<I_holidayCalendar>(new Calendar::noCalendar())); 

    void setFrequency(interval freq);
    void setStart(const finDate& start);
    void setMaturity(const finDate& maturity);
    void setDayrule(std::unique_ptr<I_dayAdjustment> dayRule);
    void setStubConvention(std::unique_ptr<I_stub> stubConvention);

    void printSchedule() const;

    // Next date const / non-const and return type?
    // Previous date

};

#endif