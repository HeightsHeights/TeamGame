#pragma once

#include "./vector3f.h"

#define Vector2f_MAX_SIZE 2

#define Vector2f_ZERO Vector2f(0, 0)

/******************************************************************************
 * class Vector2f
******************************************************************************/
class Vector2f
{
public:
  //フィールド
  float x;
  float y;

  //コンストラクタ
  Vector2f();
  Vector2f(float x, float y);

  //演算子のオーバーロード
  Vector2f operator+(Vector2f obj);
  Vector2f operator-(Vector2f obj);
  Vector2f operator*(float scalar);
  Vector2f operator/(float scalar);
  Vector2f operator=(Vector2f obj);
  Vector2f operator+=(Vector2f obj);
  Vector2f operator-=(Vector2f obj);
  Vector2f operator*=(float scalar);
  Vector2f operator/=(float scalar);
  Vector2f operator+();
  Vector2f operator-();

  operator float *() { return (float *)&x; }
  operator const float *() const { return (const float *)&x; }

  float magnitudeSquared();
  float magnitude();
  Vector2f normalize();
  static float dot(Vector2f a, Vector2f b);
  static Vector3f cross(Vector2f a, Vector2f b);
};