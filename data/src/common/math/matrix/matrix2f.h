#pragma once

#include "../vector/vector2f.h"

/******************************************************************************
 * Matrix2x2f
******************************************************************************/

#define Matrix2x2f_MAX_LINE 2
#define Matrix2x2f_MAX_ROW 2
#define Matrix2x2f_MAX_SIZE Matrix2x2f_MAX_LINE *Matrix2x2f_MAX_ROW
#define Matrix2x2f_INDEX(i, j) i *Matrix2x2f_MAX_LINE + j

#define Matrix2x2f_ZERO Matrix2x2f()
const float FLOAT22_IDENTITY[Matrix2x2f_MAX_SIZE] = {1, 0, 0, 1};
#define Matrix2x2f_IDENTITY Matrix2x2f(FLOAT22_IDENTITY)

class Matrix2x2f
{
private:
public:
  float matrix[Matrix2x2f_MAX_SIZE];
  Matrix2x2f();
  Matrix2x2f(const float matrix[Matrix2x2f_MAX_SIZE]);
  operator float *() { return (float *)matrix; }
  operator const float *() const { return (const float *)matrix; }

  Matrix2x2f operator+(Matrix2x2f obj);
  Matrix2x2f operator-(Matrix2x2f obj);
  Matrix2x2f operator*(Matrix2x2f obj);
  Vector2f operator*(Vector2f obj);
  Matrix2x2f operator*(float scalar);
  Matrix2x2f operator/(float scalar);
  Matrix2x2f operator=(Matrix2x2f obj);
  Matrix2x2f operator+=(Matrix2x2f obj);
  Matrix2x2f operator-=(Matrix2x2f obj);
  Matrix2x2f operator*=(Matrix2x2f obj);
  Matrix2x2f operator*=(float scalar);
  Matrix2x2f operator/=(float scalar);
  Matrix2x2f operator+();
  Matrix2x2f operator-();

  float getElement(unsigned int i, unsigned int j);
  float determinant();
  bool isRegularMatrix();
  Matrix2x2f *getInverseMatrix();
  void callMe();
};
