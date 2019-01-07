#include "./random.h"

#include <stdlib.h>
#include <time.h>

bool Random::init()
{
    srand((unsigned int)time(NULL));
    return true;
}

int Random::randIntBetween(const int min, const int max)
{
    return min + (int)(rand() * (max - min + 1.0) / (1.0 + RAND_MAX));
}

float Random::randFloatBetween(const float min, const float max)
{
    return min + (float)(rand() * (max - min + 1.0) / (1.0 + RAND_MAX));
}