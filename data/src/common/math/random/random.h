#pragma once

class Random
{
  private:
  public:
    static bool init();
    int randIntBetween(const int min, const int max);
    float randFloatBetween(const float min, const float max);
};