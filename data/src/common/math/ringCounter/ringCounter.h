#pragma once

class RingCounter
{
  private:
    int num;

    int min;
    int max;

  public:
    RingCounter();
    RingCounter(const int initialValue, const int min, const int max);

    int increment();
    int decrement();

    int getCount();

    int operator++();
    int operator--();
};