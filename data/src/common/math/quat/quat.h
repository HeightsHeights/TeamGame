#pragma once

#include "../touple/touple4f.h"

#define Quaternion4f_ZERO Quaternion4f()

class Quaternion4f : public Touple4f
{
private:
public:
  Quaternion4f();
  Quaternion4f(float x, float y, float z, float w);

  Quaternion4f operator+(Quaternion4f obj);
  Quaternion4f operator-(Quaternion4f obj);
  Quaternion4f operator*(float scalar);
  Quaternion4f operator/(float scalar);
  Quaternion4f operator=(Quaternion4f obj);
  Quaternion4f operator+=(Quaternion4f obj);
  Quaternion4f operator-=(Quaternion4f obj);
  Quaternion4f operator*=(float scalar);
  Quaternion4f operator/=(float scalar);
  Quaternion4f operator+();
  Quaternion4f operator-();
};