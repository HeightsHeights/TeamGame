/******************************************************************************
 * Touple4f関係に必要なヘッダーの読み込み
******************************************************************************/
#include "./touple4f.h"
#include <cmath>
#include <stdio.h>

/******************************************************************************
 * Touple4f
******************************************************************************/
Touple4f::Touple4f()
{
    this->x = 0;
    this->y = 0;
    this->z = 0;
    this->w = 0;
}
Touple4f::Touple4f(float x, float y, float z, float w)
{
    this->x = x;
    this->y = y;
    this->z = z;
    this->w = w;
}
//演算子のオーバーロード///////////////////////////////////////////////////////

/***********************************
 * +演算子のオーバーロード
 * 引数：右辺のベクトル
 * 機能：ベクトルの足し算
************************************/
Touple4f Touple4f::operator+(Touple4f obj)
{
    return Touple4f(this->x + obj.x, this->y + obj.y, this->z + obj.z, this->w + obj.w);
}
/***********************************
 * -演算子のオーバーロード
 * 引数：右辺のベクトル
 * 機能：ベクトルの減算
************************************/
Touple4f Touple4f::operator-(Touple4f obj)
{
    return *this + (-obj);
}
/***********************************
 * *演算子のオーバーロード
 * 引数：右辺のスカラー
 * 機能：ベクトルのスカラー倍
************************************/
Touple4f Touple4f::operator*(float scalar)
{
    return Touple4f(this->x * scalar, this->y * scalar, this->z * scalar, this->w * scalar);
}
/***********************************
 * /演算子のオーバーロード
 * 引数：右辺のスカラー
 * 機能：ベクトルのスカラーの逆数倍
************************************/
Touple4f Touple4f::operator/(float scalar)
{
    return *this * (1 / scalar);
}
/***********************************
 * =演算子のオーバーロード
 * 引数：右辺のベクトル
 * 機能：ベクトル同士の代入
************************************/
Touple4f Touple4f::operator=(Touple4f obj)
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
Touple4f Touple4f::operator+=(Touple4f obj)
{
    *this = *this + obj;
    return *this;
}
Touple4f Touple4f::operator-=(Touple4f obj)
{
    *this = *this - obj;
    return *this;
}
Touple4f Touple4f::operator*=(float scalar)
{
    *this = *this * scalar;
    return *this;
}
Touple4f Touple4f::operator/=(float scalar)
{
    *this = *this / scalar;
    return *this;
}
/***********************************
 * +演算子のオーバーロード
 * 引数：なし
 * 機能：特に意味離し
************************************/
Touple4f Touple4f::operator+()
{
    return *this;
}
/***********************************
 * -演算子のオーバーロード
 * 引数：なし
 * 機能：逆ベクトル
************************************/
Touple4f Touple4f::operator-()
{
    return *this * -1;
}

void Touple4f::callMe()
{
    printf("%4f\t%4f\t%4f\t%4f\n", this->x, this->y, this->z, this->w);
    printf("\n\n\n");
}