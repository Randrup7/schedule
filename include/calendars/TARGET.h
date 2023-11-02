#ifndef TARGET_H
#define TARGET_H

#include "I_calendar.h"
#include "../time/date.h"

namespace Calendar
{
// The European TARGET calendar
class TARGET : public I_calendar
{
public:
    bool isHoliday(const finDate& date) const override final;
    virtual ~TARGET() = default;
};
}

#endif