#pragma once

#include "../touple/touple4f.h"

#define Vector4f_MAX_SIZE 4

#define Vector4f_ZERO Vector4f(0, 0, 0, 0)

class Vector4f : public Touple4f
{
private:
public:
  Vector4f();
  Vector4f(float x, float y, float z, float w);
  operator float *() { return (float *)&x; }
  operator const float *() const { return (const float *)&x; }
};