#ifndef STUB_H
#define STUB_H

#include <vector>
#include "../time/date.h"

// The base interface class for stubs
class I_stub
{
public:
    virtual void fillSchedule(std::vector<finDate>& paymentDates, const finDate& start, const finDate& maturity, const interval& freq) = 0;
    virtual ~I_stub() = default;
};


namespace stub
{
class ShortInitial : public I_stub
{
public:
    void fillSchedule(std::vector<finDate>& paymentDates, const finDate& start, const finDate& maturity, const interval& freq) override final;
    virtual ~ShortInitial() = default;
};
    
class LongInitial : public I_stub
{
public:
    void fillSchedule(std::vector<finDate>& paymentDates, const finDate& start, const finDate& maturity, const interval& freq) override final;
    virtual ~LongInitial() = default;
};

class ShortFinal : public I_stub
{
public:
    void fillSchedule(std::vector<finDate>& paymentDates, const finDate& start, const finDate& maturity, const interval& freq) override final;
    virtual ~ShortFinal() = default;
};

class LongFinal : public I_stub
{
public:
    void fillSchedule(std::vector<finDate>& paymentDates, const finDate& start, const finDate& maturity, const interval& freq) override final;
    virtual ~LongFinal() = default;
};

} // namespace stub

#endif