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

Touple3f Touple3f::operator=(Touple3f obj)
{
    this->x = obj.x;
    this->y = obj.y;
    this->z = obj.z;
}

void Touple3f::callMe()
{
    printf("%4f\t%4f\t%4f\n", this->x, this->y, this->z);
    printf("\n\n\n");
}