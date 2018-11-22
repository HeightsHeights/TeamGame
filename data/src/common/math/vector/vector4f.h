#pragma once

#include "../touple/vector4f.h"

class Vector4f : public Touple4f
{
private:
public:
  Vector4f();
  Vector4f(float x, float y, float z, float w);
  operator float *() { return (float *)&x; }
  operator const float *() const { return (const float *)&x; }
};
