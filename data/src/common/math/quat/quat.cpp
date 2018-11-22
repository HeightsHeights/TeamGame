#include "quat.h"

Quaternion4f::Quaternion4f() : Touple4f()
{
}
Quaternion4f::Quaternion4f(float x, float y, float z, float w) : Touple4f(x, y, z, w)
{
}
//演算子のオーバーロード///////////////////////////////////////////////////////

/***********************************
 * +演算子のオーバーロード
 * 引数：右辺のベクトル
 * 機能：ベクトルの足し算
************************************/
Quaternion4f Quaternion4f::operator+(Quaternion4f obj)
{
    return Quaternion4f(this->x + obj.x, this->y + obj.y, this->z + obj.z, this->w + obj.w);
}
/***********************************
 * -演算子のオーバーロード
 * 引数：右辺のベクトル
 * 機能：ベクトルの減算
************************************/
Quaternion4f Quaternion4f::operator-(Quaternion4f obj)
{
    return *this + (-obj);
}
/***********************************
 * *演算子のオーバーロード
 * 引数：右辺のスカラー
 * 機能：ベクトルのスカラー倍
************************************/
Quaternion4f Quaternion4f::operator*(float scalar)
{
    return Quaternion4f(this->x * scalar, this->y * scalar, this->z * scalar, this->w * scalar);
}
/***********************************
 * /演算子のオーバーロード
 * 引数：右辺のスカラー
 * 機能：ベクトルのスカラーの逆数倍
************************************/
Quaternion4f Quaternion4f::operator/(float scalar)
{
    return *this * (1 / scalar);
}
/***********************************
 * =演算子のオーバーロード
 * 引数：右辺のベクトル
 * 機能：ベクトル同士の代入
************************************/
Quaternion4f Quaternion4f::operator=(Quaternion4f obj)
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
Quaternion4f Quaternion4f::operator+=(Quaternion4f obj)
{
    *this = *this + obj;
    return *this;
}
Quaternion4f Quaternion4f::operator-=(Quaternion4f obj)
{
    *this = *this - obj;
    return *this;
}
Quaternion4f Quaternion4f::operator*=(float scalar)
{
    *this = *this * scalar;
    return *this;
}
Quaternion4f Quaternion4f::operator/=(float scalar)
{
    *this = *this / scalar;
    return *this;
}
/***********************************
 * +演算子のオーバーロード
 * 引数：なし
 * 機能：特に意味離し
************************************/
Quaternion4f Quaternion4f::operator+()
{
    return *this;
}
/***********************************
 * -演算子のオーバーロード
 * 引数：なし
 * 機能：逆ベクトル
************************************/
Quaternion4f Quaternion4f::operator-()
{
    return *this * -1;
}