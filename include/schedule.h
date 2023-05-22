#ifndef SCHEDULE_H
#define SCHEDULE_H

#include <vector>
#include "dayCount.h"
#include "dayAdjustment.h"
#include "stub.h"

class schedule
{
private:
    finDate m_start; 
    finDate m_maturity;
    unsigned int m_freq;
    std::unique_ptr<I_dayAdjustment> m_dayRule;
    std::unique_ptr<I_stub> m_stubConvention;
    std::shared_ptr<I_holidayCalendar> m_holidayCalendar;
    
    std::vector<finDate> m_paymentDates;

    void calculateSchedule();

public:
    schedule(finDate start, finDate maturity, unsigned int freq, 
            std::unique_ptr<I_dayAdjustment> dayRule, std::unique_ptr<I_stub> stubConvention, 
            std::shared_ptr<I_holidayCalendar> m_holidayCalendar = std::shared_ptr<I_holidayCalendar>(new Calendar::noCalendar())); 

    void setFrequency(unsigned int freq);
    void setStart(const finDate& start);
    void setMaturity(const finDate& maturity);
    void setDayrule(std::unique_ptr<I_dayAdjustment> dayRule);
    void setStubConvention(std::unique_ptr<I_stub> stubConvention);

};

#endif