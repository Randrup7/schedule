#include "stub.h"

void stub::ShortInitial::fillSchedule(std::vector<finDate>& paymentDates, const finDate& start, const finDate& maturity, const int freq)
{
    finDate dateCounter = maturity;
    int step = 12 / freq;

    while (dateCounter > start)
    {
        paymentDates.push_back(dateCounter);
        dateCounter.addMonths(-(step));
    }

    paymentDates.push_back(start);

    std::reverse(paymentDates.begin(), paymentDates.end());
}

void stub::LongInitial::fillSchedule(std::vector<finDate>& paymentDates, const finDate& start, const finDate& maturity, const int freq)
{
    finDate dateCounter = maturity;
    int step = 12 / freq;

    while (dateCounter > start)
    {
        paymentDates.push_back(dateCounter);
        dateCounter.addMonths(-(step));
    }
    paymentDates.pop_back();
    paymentDates.push_back(start);

    std::reverse(paymentDates.begin(), paymentDates.end());
}

void stub::ShortFinal::fillSchedule(std::vector<finDate>& paymentDates, const finDate& start, const finDate& maturity, const int freq)
{
    finDate dateCounter = start;
    int step = 12 / freq;

    while (dateCounter < maturity)
    {
        paymentDates.push_back(dateCounter);
        dateCounter.addMonths(step);
    }

    paymentDates.push_back(maturity);
}

void stub::LongFinal::fillSchedule(std::vector<finDate>& paymentDates, const finDate& start, const finDate& maturity, const int freq)
{
    finDate dateCounter = start;
    int step = 12 / freq;

    while (dateCounter < maturity)
    {
        paymentDates.push_back(dateCounter);
        dateCounter.addMonths(step);
    }

    paymentDates.pop_back();
    paymentDates.push_back(maturity);
}