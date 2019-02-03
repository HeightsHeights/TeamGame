#include "./ringCounter.h"

RingCounter::RingCounter()
{
}
RingCounter::RingCounter(const int initialValue, const int min, const int max)
{
    this->min = min;
    this->max = max;

    this->num = initialValue;
}

int RingCounter::increment()
{
    num++;
    if (num > max)
    {
        num = min;
    }
    return this->num;
}
int RingCounter::decrement()
{
    num--;
    if (num < min)
    {
        num = max;
    }
    return this->num;
}
int RingCounter::getCount()
{
    return this->num;
}
bool RingCounter::isMin()
{
    return this->num == this->min;
}
bool RingCounter::isMax()
{
    return this->num == this->max;
}

int RingCounter::operator++()
{
    return this->increment();
}
int RingCounter::operator--()
{
    return this->decrement();
}