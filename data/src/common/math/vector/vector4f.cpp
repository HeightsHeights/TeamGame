#include "./vector4f.h"

#include <cmath>
#include <stdio.h>

Vector4f::Vector4f() : Touple4f()
{
}
Vector4f::Vector4f(float x, float y, float z, float w) : Touple4f(x, y, z, w)
{
}
//演算子のオーバーロード///////////////////////////////////////////////////////

/***********************************
 * +演算子のオーバーロード
 * 引数：右辺のベクトル
 * 機能：ベクトルの足し算
************************************/
Vector4f Vector4f::operator+(Vector4f obj)
{
    return Vector4f(this->x + obj.x, this->y + obj.y, this->z + obj.z, this->w + obj.w);
}
/***********************************
 * -演算子のオーバーロード
 * 引数：右辺のベクトル
 * 機能：ベクトルの減算
************************************/
Vector4f Vector4f::operator-(Vector4f obj)
{
    return *this + (-obj);
}
/***********************************
 * *演算子のオーバーロード
 * 引数：右辺のスカラー
 * 機能：ベクトルのスカラー倍
************************************/
Vector4f Vector4f::operator*(float scalar)
{
    return Vector4f(this->x * scalar, this->y * scalar, this->z * scalar, this->w * scalar);
}
/***********************************
 * /演算子のオーバーロード
 * 引数：右辺のスカラー
 * 機能：ベクトルのスカラーの逆数倍
************************************/
Vector4f Vector4f::operator/(float scalar)
{
    return *this * (1 / scalar);
}
/***********************************
 * =演算子のオーバーロード
 * 引数：右辺のベクトル
 * 機能：ベクトル同士の代入
************************************/
Vector4f Vector4f::operator=(Vector4f obj)
{
    this->x = obj.x;
    this->y = obj.y;
    this->z = obj.z;
    this->w = obj.w;
    return *this;
}
/***********************************
 * その他代入演算子
************************************/
Vector4f Vector4f::operator+=(Vector4f obj)
{
    *this = *this + obj;
    return *this;
}
Vector4f Vector4f::operator-=(Vector4f obj)
{
    *this = *this - obj;
    return *this;
}
Vector4f Vector4f::operator*=(float scalar)
{
    *this = *this * scalar;
    return *this;
}
Vector4f Vector4f::operator/=(float scalar)
{
    *this = *this / scalar;
    return *this;
}
/***********************************
 * +演算子のオーバーロード
 * 引数：なし
 * 機能：特に意味離し
************************************/
Vector4f Vector4f::operator+()
{
    return *this;
}
/***********************************
 * -演算子のオーバーロード
 * 引数：なし
 * 機能：逆ベクトル
************************************/
Vector4f Vector4f::operator-()
{
    return *this * -1;
}

//メソッド/////////////////////////////////////////////////////////////////////
/***********************************
 * 引数：なし
 * 戻り値：絶対値の二乗
************************************/
float Vector4f::magnitudeSquared()
{
    return (float)(std::pow(x, 2.0) + std::pow(y, 2.0) + std::pow(z, 2.0) + std::pow(w, 2.0));
}
/***********************************
 * 引数：なし
 * 戻り値：絶対値
************************************/
float Vector4f::magnitude()
{
    return (float)sqrt(magnitudeSquared());
}
/***********************************
 * 引数：なし
 * 戻り値：正規化されたベクトル
************************************/
Vector4f Vector4f::normalize()
{
    float m = magnitude();
    return *this / m;
}
/***********************************
 * 引数：内積を取りたいベクトル2つ
 * 戻り値：内積の値
************************************/
float Vector4f::dot(Vector4f a, Vector4f b)
{
    return a.x * b.x + a.y * b.y + a.z * b.z + a.w * b.w;
}