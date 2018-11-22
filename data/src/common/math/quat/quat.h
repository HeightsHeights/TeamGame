#pragma once

#include "../touple/touple4f.h"

class Quaternion4f : public Touple4f
{
private:
public:
  Quaternion4f();
  Quaternion4f(float x, float y, float z, float w);
};