#pragma once

#define Vector3f_ZERO *new Vector3f(0, 0, 0)
#define Vector2f_ZERO *new Vector2f(0, 0)
/////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////
class Vector3f
{
public:
  //フィールド
  float x;
  float y;
  float z;

  //演算子のオーバーロード
  Vector3f operator+(Vector3f obj);
  Vector3f operator-(Vector3f obj);
  Vector3f operator*(float scalar);
  Vector3f operator/(float scalar);
  Vector3f operator=(Vector3f obj);
  Vector3f operator+();
  Vector3f operator-();

  //コンストラクタ
  Vector3f();
  Vector3f(float x, float y, float z);

  //メソッド
  float magnitudeSquared();
  float magnitude();
  Vector3f normalize();
  static float dot(Vector3f a, Vector3f b);
  static Vector3f cross(Vector3f a, Vector3f b);
  Vector3f matrixMultiplication(float matrix[3][3]);
  Vector3f scaling(Vector3f scale_vector);
  Vector3f rotate(Vector3f v, float angle);
  float betweenAngleRdian(Vector3f v);
  float betweenAngleDegree(Vector3f v);
};
/////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////
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
  Vector2f operator+();
  Vector2f operator-();

  float magnitudeSquared();
  float magnitude();
  Vector2f normalize();
  static float dot(Vector2f a, Vector2f b);
  static Vector3f cross(Vector2f a, Vector2f b);
};