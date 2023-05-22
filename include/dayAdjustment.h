#ifndef DAYADJUSTMENT_H
#define DAYADJUSTMENT_H

#include <chrono>
#include "date.h"
#include "holidayCalendar.h"

// The base interface class for dayadjustments
class I_dayAdjustment
{
public:
    virtual void adjustDate(finDate& date, 
        std::shared_ptr<I_holidayCalendar> calendar) = 0;
    virtual ~I_dayAdjustment() = default;
};

// Placing the derived classes of dayAjustment in a namespace
namespace dayAdjustment
{
// Modified following dayrule class
class MF : public I_dayAdjustment
{
public:
    void adjustDate(finDate& date, std::shared_ptr<I_holidayCalendar> calendar) override final;
    virtual ~MF() = default;
};

// Following dayrule class
class F : public I_dayAdjustment
{
public:
    void adjustDate(finDate& date, std::shared_ptr<I_holidayCalendar> calendar) override final;
    virtual ~F() = default;
};

// Previous dayrule class
class P : public I_dayAdjustment
{
public:
    void adjustDate(finDate& date, std::shared_ptr<I_holidayCalendar> calendar) override final;
    virtual ~P() = default;
};

// Unadjusted dayrule class
class Unadjusted : public I_dayAdjustment
{
public:
    void adjustDate(finDate& date, std::shared_ptr<I_holidayCalendar> calendar) override final {};
    virtual ~Unadjusted() = default;
};

} // namespace dayAdjustment

#endif