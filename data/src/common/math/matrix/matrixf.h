#pragma once

#include "../touple/quat.h"
#include "../vector/vector.h"

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
  void callMe();
};

/******************************************************************************
 * Matrix3x3f
******************************************************************************/
#define Matrix3x3f_MAX_LINE 3
#define Matrix3x3f_MAX_ROW 3
#define Matrix3x3f_MAX_SIZE Matrix3x3f_MAX_LINE *Matrix3x3f_MAX_ROW

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
  void callMe();
};