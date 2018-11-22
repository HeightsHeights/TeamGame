/******************************************************************************
 * Touple2f関係に必要なヘッダーの読み込み
******************************************************************************/
#include "./touple2f.h"
#include <cmath>
#include <stdio.h>

/******************************************************************************
 * Touple2f
******************************************************************************/
//コンストラクタ///////////////////////////////////////////////////////////////
Touple2f::Touple2f()
{
    this->x = 0;
    this->y = 0;
}
Touple2f::Touple2f(float x, float y)
{
    this->x = x;
    this->y = y;
}

//OverLoad///////////////////////////////////////////////////////////////
/***********************************
 * +演算子のオーバーロード
 * 引数：右辺のベクトル
 * 機能：ベクトルの足し算
************************************/
Touple2f Touple2f::operator+(Touple2f obj)
{
    return Touple2f(this->x + obj.x, this->y + obj.y);
}
/***********************************
 * -演算子のオーバーロード
 * 引数：右辺のベクトル
 * 機能：ベクトルの減算
************************************/
Touple2f Touple2f::operator-(Touple2f obj)
{
    return Touple2f(this->x - obj.x, this->y - obj.y);
}
/***********************************
 * *演算子のオーバーロード
 * 引数：右辺のスカラー
 * 機能：ベクトルのスカラー倍
************************************/
Touple2f Touple2f::operator*(float scalar)
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
Touple2f Touple2f::operator/(float scalar)
{
    return *this * (1 / scalar);
}
/***********************************
 * =演算子のオーバーロード
 * 引数：右辺のベクトル
 * 機能：ベクトル同士の代入
************************************/
Touple2f Touple2f::operator=(Touple2f obj)
{
    this->x = obj.x;
    this->y = obj.y;
    return *this;
}
/***********************************
 * その他代入演算子
************************************/
Touple2f Touple2f::operator+=(Touple2f obj)
{
    *this = *this + obj;
    return *this;
}
Touple2f Touple2f::operator-=(Touple2f obj)
{
    *this = *this - obj;
    return *this;
}
Touple2f Touple2f::operator*=(float scalar)
{
    *this = *this * scalar;
    return *this;
}
Touple2f Touple2f::operator/=(float scalar)
{
    *this = *this / scalar;
    return *this;
}
/***********************************
 * +演算子のオーバーロード
 * 引数：なし
 * 機能：特に意味離し
************************************/
Touple2f Touple2f::operator+()
{
    return *this;
}
/***********************************
 * -演算子のオーバーロード
 * 引数：なし
 * 機能：逆ベクトル
************************************/
Touple2f Touple2f::operator-()
{
    return *this * -1;
}

void Touple2f::callMe()
{
    printf("%4f\t%4f\n", this->x, this->y);
    printf("\n\n\n");
}