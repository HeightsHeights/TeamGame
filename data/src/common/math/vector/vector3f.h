#pragma once

#include "../touple/touple3f.h"

#define Vector3f_MAX_SIZE 3

#define Vector3f_ZERO Vector3f(0, 0, 0)

/******************************************************************************
 * class Vector3f
******************************************************************************/
class Vector3f : public Touple3f
{
public:
  //コンストラクタ
  Vector3f();
  Vector3f(float x, float y, float z);

  //演算子のオーバーロード
  Vector3f operator+(Vector3f obj);
  Vector3f operator-(Vector3f obj);
  Vector3f operator*(float scalar);
  Vector3f operator/(float scalar);
  Vector3f operator=(Vector3f obj);
  Vector3f operator+=(Vector3f obj);
  Vector3f operator-=(Vector3f obj);
  Vector3f operator*=(float scalar);
  Vector3f operator/=(float scalar);
  Vector3f operator+();
  Vector3f operator-();
  bool operator==(Vector3f obj);
  bool operator!=(Vector3f obj);

  //メソッド
  float magnitudeSquared();
  float magnitude();
  Vector3f normalize();
  static float dot(Vector3f a, Vector3f b);
  static Vector3f cross(Vector3f a, Vector3f b);
  Vector3f scaling(Vector3f scaleVector);
  Vector3f rotate(Vector3f v, float angle);
  float betweenAngleRdian(Vector3f v);
  float betweenAngleDegree(Vector3f v);
};