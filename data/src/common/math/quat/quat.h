#pragma once

#include "../matrix/matrix4f.h"
#include "../vector/vector3f.h"

#define Quaternion4f_ZERO Quaternion4f()

class Matrix4x4f;
class Quaternion4f
{
private:
public:
  float w;
  Vector3f v;

  Quaternion4f();
  Quaternion4f(float w, Vector3f v);
  Quaternion4f(Vector3f position);
  Quaternion4f(float w, float x, float y, float z);
  Quaternion4f(Vector3f axis, float theta);

  Quaternion4f operator*(Quaternion4f obj);
  Quaternion4f operator=(Quaternion4f obj);
  Quaternion4f operator*=(Quaternion4f obj);

  operator float *() { return (float *)&w; }
  operator const float *() const { return (const float *)&w; }

  Quaternion4f getConjugate();

  Matrix4x4f toMatrix();

  static Vector3f rotate(Vector3f p, Vector3f v, float angle);

  void callMe();
};