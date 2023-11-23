#include "forwardRate.h"

forwardRate::forwardRate(finDate anchor, finDate start, finDate maturity, 
    std::shared_ptr<I_dayCount> daycount, std::shared_ptr<I_dayAdjustment> dayAdjustment,
    std::shared_ptr<I_calendar> calendar, std::shared_ptr<I_interpolate> interpolate)
    : m_daycount{ daycount }, m_dayAdjustment{ dayAdjustment }, m_calendar { calendar }, m_interpolate{ interpolate }
{
    if (start >= maturity)
    {
        throw std::invalid_argument( "forwardRate constructor: start date larger or equal to maturity date." );
    }
    if (anchor > start)
    {
        throw std::invalid_argument( "forwardRate constructor: start date less than anchor date." );
    }

    m_anchor = anchor;
    m_start = start;
    m_maturity = maturity;
}