/******************************************************************************
 * Touple3f関係に必要なヘッダーの読み込み
******************************************************************************/
#include "./touple3f.h"
#include <cmath>
#include <stdio.h>

/******************************************************************************
 * Touple3f
******************************************************************************/
Touple3f::Touple3f()
{
    this->x = 0;
    this->y = 0;
    this->z = 0;
}
Touple3f::Touple3f(float x, float y, float z)
{
    this->x = x;
    this->y = y;
    this->z = z;
}

//OverLoad///////////////////////////////////////////////////////////////
/***********************************
 * +演算子のオーバーロード
 * 引数：右辺のベクトル
 * 機能：ベクトルの足し算
************************************/
Touple3f Touple3f::operator+(Touple3f obj)
{
    return Touple3f(this->x + obj.x, this->y + obj.y, this->z + obj.z);
}
/***********************************
 * -演算子のオーバーロード
 * 引数：右辺のベクトル
 * 機能：ベクトルの減算
************************************/
Touple3f Touple3f::operator-(Touple3f obj)
{
    return *this + (-obj);
}
/***********************************
 * *演算子のオーバーロード
 * 引数：右辺のスカラー
 * 機能：ベクトルのスカラー倍
************************************/
Touple3f Touple3f::operator*(float scalar)
{
    return Touple3f(this->x * scalar, this->y * scalar, this->z * scalar);
}
/***********************************
 * /演算子のオーバーロード
 * 引数：右辺のスカラー
 * 機能：ベクトルのスカラーの逆数倍
************************************/
Touple3f Touple3f::operator/(float scalar)
{
    return *this * (1 / scalar);
}
/***********************************
 * =演算子のオーバーロード
 * 引数：右辺のベクトル
 * 機能：ベクトル同士の代入
************************************/
Touple3f Touple3f::operator=(Touple3f obj)
{
    this->x = obj.x;
    this->y = obj.y;
    this->z = obj.z;
    return *this;
}
/***********************************
 * その他代入演算子
************************************/
Touple3f Touple3f::operator+=(Touple3f obj)
{
    *this = *this + obj;
    return *this;
}
Touple3f Touple3f::operator-=(Touple3f obj)
{
    *this = *this - obj;
    return *this;
}
Touple3f Touple3f::operator*=(float scalar)
{
    *this = *this * scalar;
    return *this;
}
Touple3f Touple3f::operator/=(float scalar)
{
    *this = *this / scalar;
    return *this;
}

void Touple3f::callMe()
{
    printf("%4f\t%4f\t%4f\n", this->x, this->y, this->z);
    printf("\n\n\n");
}