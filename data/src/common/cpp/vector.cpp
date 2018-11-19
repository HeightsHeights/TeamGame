#include "../header/matrixf.h"
/******************************************************************************
 * ベクトル関係に必要なヘッダーの読み込み
******************************************************************************/
#include "../header/vector.h"
#include <cmath>
#include <stdio.h>

/******************************************************************************
 * class Vector3f
******************************************************************************/

//コンストラクタ///////////////////////////////////////////////////////////////
/***********************************
 * コンストラクタ
 * 引数：なし
************************************/
Vector3f::Vector3f()
{
    x = 0;
    y = 0;
    z = 0;
}
/***********************************
 * コンストラクタ
 * 引数：ベクトルの成分
 * 機能：それぞれの成分を初期化
************************************/
Vector3f::Vector3f(float x, float y, float z)
{
    this->x = x;
    this->y = y;
    this->z = z;
}

//演算子のオーバーロード///////////////////////////////////////////////////////

/***********************************
 * +演算子のオーバーロード
 * 引数：右辺のベクトル
 * 機能：ベクトルの足し算
************************************/
Vector3f Vector3f::operator+(Vector3f obj)
{
    return Vector3f(this->x + obj.x, this->y + obj.y, this->z + obj.z);
}
/***********************************
 * -演算子のオーバーロード
 * 引数：右辺のベクトル
 * 機能：ベクトルの減算
************************************/
Vector3f Vector3f::operator-(Vector3f obj)
{
    return Vector3f(this->x - obj.x, this->y - obj.y, this->z - obj.z);
}
/***********************************
 * *演算子のオーバーロード
 * 引数：右辺のスカラー
 * 機能：ベクトルのスカラー倍
************************************/
Vector3f Vector3f::operator*(float scalar)
{
    return Vector3f(this->x * scalar, this->y * scalar, this->z * scalar);
}
/***********************************
 * /演算子のオーバーロード
 * 引数：右辺のスカラー
 * 機能：ベクトルのスカラーの逆数倍
************************************/
Vector3f Vector3f::operator/(float scalar)
{

    return *this * (1 / scalar);
}
/***********************************
 * =演算子のオーバーロード
 * 引数：右辺のベクトル
 * 機能：ベクトル同士の代入
************************************/
Vector3f Vector3f::operator=(Vector3f obj)
{
    this->x = obj.x;
    this->y = obj.y;
    this->z = obj.z;
    return *this;
}
/***********************************
 * その他代入演算子
************************************/
Vector3f Vector3f::operator+=(Vector3f obj)
{
    *this = *this + obj;
    return *this;
}
Vector3f Vector3f::operator-=(Vector3f obj)
{
    *this = *this - obj;
    return *this;
}
Vector3f Vector3f::operator*=(float scalar)
{
    *this = *this * scalar;
    return *this;
}
Vector3f Vector3f::operator/=(float scalar)
{
    *this = *this / scalar;
    return *this;
}
/***********************************
 * +演算子のオーバーロード
 * 引数：なし
 * 機能：特に意味離し
************************************/
Vector3f Vector3f::operator+()
{
    return *this;
}
/***********************************
 * -演算子のオーバーロード
 * 引数：なし
 * 機能：逆ベクトル
************************************/
Vector3f Vector3f::operator-()
{
    return *this * -1;
}

//メソッド/////////////////////////////////////////////////////////////////////
/***********************************
 * 引数：なし
 * 戻り値：絶対値の二乗
************************************/
float Vector3f::magnitudeSquared()
{
    return (float)(std::pow(x, 2.0) + std::pow(y, 2.0) + std::pow(z, 2.0));
}
/***********************************
 * 引数：なし
 * 戻り値：絶対値
************************************/
float Vector3f::magnitude()
{
    return (float)sqrt(magnitudeSquared());
}
/***********************************
 * 引数：なし
 * 戻り値：正規化されたベクトル
************************************/
Vector3f Vector3f::normalize()
{
    float m = magnitude();
    return *this / m;
}
/***********************************
 * 引数：内積を取りたいベクトル2つ
 * 戻り値：内積の値
************************************/
float Vector3f::dot(Vector3f a, Vector3f b)
{
    return a.x * b.x + a.y * b.y + a.z * b.z;
}
/***********************************
 * 引数：外積を取りたいベクトル2つ
 * 戻り値：外積によって生じるベクトル
************************************/
Vector3f Vector3f::cross(Vector3f a, Vector3f b)
{
    return Vector3f(a.y * b.z - a.z * b.y, a.z * b.x - a.x * b.z, a.x * b.y - a.y * b.x);
}

/***********************************
 * 引数：スケール用のベクトル
 * 戻り値：スケーリングされたベクトル
************************************/
Vector3f Vector3f::scaling(Vector3f scaleVector)
{
    return Vector3f(x * scaleVector.x, y * scaleVector.y, z * scaleVector.z);
}

/***********************************
 * 引数：回転の軸と回転の角度
 * 戻り値：回転したベクトル
************************************/
Vector3f Vector3f::rotate(Vector3f v, float angle)
{
    v = v.normalize();
    Matrix3x3f rotationMatrix;
    float Radian_angle = angle * M_PI / 180.0f;

    float COSINE = (float)std::cos(Radian_angle);
    float SINE = (float)std::sin(Radian_angle);

    rotationMatrix[0] = COSINE + (float)std::pow(v.x, 2.0) * (1.0f - COSINE);
    rotationMatrix[1] = v.x * v.y * (1.0f - COSINE) - v.z * SINE;
    rotationMatrix[2] = v.x * v.z * (1.0f - COSINE) + v.y * SINE;

    rotationMatrix[3] = v.y * v.x * (1.0f - COSINE) + v.z * SINE;
    rotationMatrix[4] = COSINE + (float)std::pow(v.y, 2.0) * (1.0f - COSINE);
    rotationMatrix[5] = v.y * v.z * (1.0f - COSINE) - v.x * SINE;

    rotationMatrix[6] = v.z * v.x * (1.0f - COSINE) - v.y * SINE;
    rotationMatrix[7] = v.z * v.y * (1.0f - COSINE) + v.x * SINE;
    rotationMatrix[8] = COSINE + (float)std::pow(v.z, 2.0) * (1.0f - COSINE);

    Vector3f ret = rotationMatrix * *this;
    return ret;
}

/***********************************
 * 引数：角度を取るベクトル
 * 戻り値：自分と引数のベクトルとの角度(弧度法)
************************************/
float Vector3f::betweenAngleRdian(Vector3f v)
{
    return acosf(dot(*this, v) / ((*this).magnitude() * v.magnitude()));
}
/***********************************
 * 引数：角度を取るベクトル
 * 戻り値：自分と引数のベクトルとの角度(度数法)
************************************/
float Vector3f::betweenAngleDegree(Vector3f v)
{
    return betweenAngleRdian(v) * 180.0f / M_PI;
}

//使い方
/*
int main()
{
  Vector3f v1(1.0f, 1.0f, 0.0f);
  Vector3f v2(3.0f, 0.0f, 1.0f);

  Vector3f v3 = -v2 * 2 + v1;
  printf("x:%f,y:%f,z:%f\n", v3.x, v3.y, v3.z);
  printf("m:%f\n", v3.magnitude());
  return 0;
}
*/

/******************************************************************************
 * class Vector2f
******************************************************************************/

//コンストラクタ///////////////////////////////////////////////////////////////
/***********************************
 * コンストラクタ
 * 引数：なし
************************************/
Vector2f::Vector2f()
{
    x = 0;
    y = 0;
}
/***********************************
 * コンストラクタ
 * 引数：ベクトルの成分
 * 機能：それぞれの成分を初期化
************************************/
Vector2f::Vector2f(float x, float y)
{
    this->x = x;
    this->y = y;
}

//演算子のオーバーロード///////////////////////////////////////////////////////

/***********************************
 * +演算子のオーバーロード
 * 引数：右辺のベクトル
 * 機能：ベクトルの足し算
************************************/
Vector2f Vector2f::operator+(Vector2f obj)
{
    return Vector2f(this->x + obj.x, this->y + obj.y);
}
/***********************************
 * -演算子のオーバーロード
 * 引数：右辺のベクトル
 * 機能：ベクトルの減算
************************************/
Vector2f Vector2f::operator-(Vector2f obj)
{
    return Vector2f(this->x - obj.x, this->y - obj.y);
}
/***********************************
 * *演算子のオーバーロード
 * 引数：右辺のスカラー
 * 機能：ベクトルのスカラー倍
************************************/
Vector2f Vector2f::operator*(float scalar)
{
    this->x *= scalar;
    this->y *= scalar;

    return *this;
}
/***********************************
 * /演算子のオーバーロード
 * 引数：右辺のスカラー
 * 機能：ベクトルのスカラーの逆数倍
************************************/
Vector2f Vector2f::operator/(float scalar)
{
    return *this * (1 / scalar);
}
/***********************************
 * =演算子のオーバーロード
 * 引数：右辺のベクトル
 * 機能：ベクトル同士の代入
************************************/
Vector2f Vector2f::operator=(Vector2f obj)
{
    this->x = obj.x;
    this->y = obj.y;
    return *this;
}
/***********************************
 * その他代入演算子
************************************/
Vector2f Vector2f::operator+=(Vector2f obj)
{
    *this = *this + obj;
    return *this;
}
Vector2f Vector2f::operator-=(Vector2f obj)
{
    *this = *this - obj;
    return *this;
}
Vector2f Vector2f::operator*=(float scalar)
{
    *this = *this * scalar;
    return *this;
}
Vector2f Vector2f::operator/=(float scalar)
{
    *this = *this / scalar;
    return *this;
}
/***********************************
 * +演算子のオーバーロード
 * 引数：なし
 * 機能：特に意味離し
************************************/
Vector2f Vector2f::operator+()
{
    return *this;
}
/***********************************
 * -演算子のオーバーロード
 * 引数：なし
 * 機能：逆ベクトル
************************************/
Vector2f Vector2f::operator-()
{
    return *this * -1;
}

//メソッド/////////////////////////////////////////////////////////////////////
/***********************************
 * 引数：なし
 * 戻り値：絶対値の二乗
************************************/
float Vector2f::magnitudeSquared()
{
    return (float)(std::pow(x, 2.0) + std::pow(y, 2.0));
}
/***********************************
 * 引数：なし
 * 戻り値：絶対値
************************************/
float Vector2f::magnitude()
{
    return (float)sqrt(magnitudeSquared());
}
/***********************************
 * 引数：なし
 * 戻り値：正規化されたベクトル
************************************/
Vector2f Vector2f::normalize()
{
    float m = magnitude();
    return *this / m;
}
/***********************************
 * 引数：内積を取りたいベクトル2つ
 * 戻り値：内積の値
************************************/
float Vector2f::dot(Vector2f a, Vector2f b)
{
    return a.x * b.x + a.y * b.y;
}
/***********************************
 * 引数：外積を取りたいベクトル2つ
 * 戻り値：外積によって生じるベクトル
************************************/
Vector3f Vector2f::cross(Vector2f a, Vector2f b)
{
    return Vector3f(0, 0, a.x * b.y - a.y * b.x);
}