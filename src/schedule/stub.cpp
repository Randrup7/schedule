#include "stub.h"

void stub::ShortInitial::fillSchedule(std::vector<finDate>& paymentDates, const finDate& start, const finDate& maturity, const interval& freq)
{
    finDate dateCounter = maturity;

    while (dateCounter > start)
    {
        paymentDates.push_back(dateCounter);
        dateCounter -= freq;
    }

    paymentDates.push_back(start);

    std::reverse(paymentDates.begin(), paymentDates.end());
}

void stub::LongInitial::fillSchedule(std::vector<finDate>& paymentDates, const finDate& start, const finDate& maturity, const interval& freq)
{
    finDate dateCounter = maturity;

    while (dateCounter > start)
    {
        paymentDates.push_back(dateCounter);
        dateCounter -= freq;
    }
    paymentDates.pop_back();
    paymentDates.push_back(start);

    std::reverse(paymentDates.begin(), paymentDates.end());
}

void stub::ShortFinal::fillSchedule(std::vector<finDate>& paymentDates, const finDate& start, const finDate& maturity, const interval& freq)
{
    finDate dateCounter = start;

    while (dateCounter < maturity)
    {
        paymentDates.push_back(dateCounter);
        dateCounter += freq;
    }

    paymentDates.push_back(maturity);
}

void stub::LongFinal::fillSchedule(std::vector<finDate>& paymentDates, const finDate& start, const finDate& maturity, const interval& freq)
{
    finDate dateCounter = start;

    while (dateCounter < maturity)
    {
        paymentDates.push_back(dateCounter);
        dateCounter += freq;
    }

    paymentDates.pop_back();
    paymentDates.push_back(maturity);
}

void stub::Zero::fillSchedule(std::vector<finDate>& paymentDates, const finDate& start, const finDate& maturity, const interval& freq)
{
    paymentDates.assign( {start, maturity} );
}