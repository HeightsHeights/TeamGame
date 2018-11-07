/******************************************************************************
 * 四元数関係に必要なヘッダーの読み込み
******************************************************************************/
#include "../header/quat.h"
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

Touple4f Touple4f::operator=(Touple4f obj)
{
    this->x = obj.x;
    this->y = obj.y;
    this->z = obj.z;
    this->w = obj.w;
}