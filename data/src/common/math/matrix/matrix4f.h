#pragma once

#include "../vector/vector4f.h"

/******************************************************************************
 * Matrix4x4f
******************************************************************************/

#define Matrix4x4f_MAX_LINE 4
#define Matrix4x4f_MAX_ROW 4
#define Matrix4x4f_MAX_SIZE Matrix4x4f_MAX_LINE *Matrix4x4f_MAX_ROW

#define Matrix4x4f_ZERO Matrix4x4f()
const float FLOAT44_IDENTITY[Matrix4x4f_MAX_SIZE] = {1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1};
#define Matrix4x4f_IDENTITY Matrix4x4f(FLOAT44_IDENTITY)

class Matrix4x4f
{
private:
public:
  float matrix[Matrix4x4f_MAX_SIZE];
  Matrix4x4f();
  Matrix4x4f(const float matrix[Matrix4x4f_MAX_SIZE]);
  operator float *() { return (float *)matrix; }
  operator const float *() const { return (const float *)matrix; }

  Matrix4x4f operator+(Matrix4x4f obj);
  Matrix4x4f operator-(Matrix4x4f obj);
  Matrix4x4f operator*(Matrix4x4f obj);
  Vector4f operator*(Vector4f obj);
  Matrix4x4f operator*(float scalar);
  Matrix4x4f operator/(float scalar);
  Matrix4x4f operator=(Matrix4x4f obj);
  Matrix4x4f operator+=(Matrix4x4f obj);
  Matrix4x4f operator-=(Matrix4x4f obj);
  Matrix4x4f operator*=(Matrix4x4f obj);
  Matrix4x4f operator*=(float scalar);
  Matrix4x4f operator/=(float scalar);
  Matrix4x4f operator+();
  Matrix4x4f operator-();

  float getElement(unsigned int i, unsigned int j);
  float determinant();
  bool isRegularMatrix();
  Matrix4x4f *getInverseMatrix();
  void callMe();
};
