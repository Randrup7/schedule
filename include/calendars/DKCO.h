#ifndef DKCO_H
#define DKCO_H

#include "I_calendar.h"
#include "../time/date.h"

namespace Calendar
{
// The Danish national holiday calendar
class DKCO : public I_calendar
{
public:
    bool isHoliday(const finDate& date) const override final;
    virtual ~DKCO() = default;
};

}

#endif