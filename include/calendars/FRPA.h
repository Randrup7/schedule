#ifndef FRPA_H
#define FRPA_H

#include "I_calendar.h"
#include "../time/date.h"

namespace Calendar
{
// The Danish national holiday calendar
class FRPA : public I_calendar
{
public:
    bool isHoliday(const finDate& date) const override final;
    virtual ~FRPA() = default;
};

}

#endif