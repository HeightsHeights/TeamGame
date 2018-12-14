#pragma once

#include "../vector/vector3f.h"

/******************************************************************************
 * Matrix3x3f
******************************************************************************/

#define Matrix3x3f_MAX_LINE 3
#define Matrix3x3f_MAX_ROW 3
#define Matrix3x3f_MAX_SIZE Matrix3x3f_MAX_LINE *Matrix3x3f_MAX_ROW
#define Matrix3x3f_INDEX(i, j) i *Matrix3x3f_MAX_LINE + j

#define Matrix3x3f_ZERO Matrix3x3f()
const float FLOAT33_IDENTITY[Matrix3x3f_MAX_SIZE] = {1, 0, 0, 0, 1, 0, 0, 0, 1};
#define Matrix3x3f_IDENTITY Matrix3x3f(FLOAT33_IDENTITY)

class Matrix3x3f
{
private:
public:
  float matrix[Matrix3x3f_MAX_SIZE];
  Matrix3x3f();
  Matrix3x3f(const float matrix[Matrix3x3f_MAX_SIZE]);
  operator float *() { return (float *)matrix; }
  operator const float *() const { return (const float *)matrix; }

  Matrix3x3f operator+(Matrix3x3f obj);
  Matrix3x3f operator-(Matrix3x3f obj);
  Matrix3x3f operator*(Matrix3x3f obj);
  Vector3f operator*(Vector3f obj);
  Matrix3x3f operator*(float scalar);
  Matrix3x3f operator/(float scalar);
  Matrix3x3f operator=(Matrix3x3f obj);
  Matrix3x3f operator+=(Matrix3x3f obj);
  Matrix3x3f operator-=(Matrix3x3f obj);
  Matrix3x3f operator*=(Matrix3x3f obj);
  Matrix3x3f operator*=(float scalar);
  Matrix3x3f operator/=(float scalar);
  Matrix3x3f operator+();
  Matrix3x3f operator-();

  float getElement(unsigned int i, unsigned int j);
  float determinant();
  bool isRegularMatrix();
  Matrix3x3f *getInverseMatrix();
  Matrix3x3f getTransverseMatrix();
  void callMe();
};
