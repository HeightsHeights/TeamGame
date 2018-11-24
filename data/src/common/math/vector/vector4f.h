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

  //演算子のオーバーロード
  Vector4f operator+(Vector4f obj);
  Vector4f operator-(Vector4f obj);
  Vector4f operator*(float scalar);
  Vector4f operator/(float scalar);
  Vector4f operator=(Vector4f obj);
  Vector4f operator+=(Vector4f obj);
  Vector4f operator-=(Vector4f obj);
  Vector4f operator*=(float scalar);
  Vector4f operator/=(float scalar);
  Vector4f operator+();
  Vector4f operator-();

  float magnitudeSquared();
  float magnitude();
  Vector4f normalize();
  static float dot(Vector4f a, Vector4f b);
};