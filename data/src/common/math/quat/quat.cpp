#include "quat.h"
#include <cmath>
#include <stdio.h>

Quaternion4f::Quaternion4f()
{
    this->w = 0;
    this->v = Vector3f_ZERO;
}
Quaternion4f::Quaternion4f(float w, Vector3f v)
{
    this->w = w;
    this->v = v;
}
Quaternion4f::Quaternion4f(Vector3f position)
{
    w = 0;
    v = position;
}
Quaternion4f::Quaternion4f(float w, float x, float y, float z)
{
    this->w = w;
    this->v = Vector3f(x, y, z);
}
Quaternion4f::Quaternion4f(Vector3f axis, float theta)
{
    float halfTheta = theta / 2;
    float cosine = cosf(halfTheta);
    float sine = sinf(halfTheta);

    w = cosine;
    v = axis * sine;
}

Quaternion4f Quaternion4f::operator*(Quaternion4f obj)
{
    Quaternion4f ret;
    ret.w = this->w * obj.w - Vector3f::dot(this->v, obj.v);
    ret.v = obj.v * this->w + this->v * obj.w + Vector3f::cross(this->v, obj.v);
    return ret;
}
Quaternion4f Quaternion4f::operator=(Quaternion4f obj)
{
    this->w = obj.w;
    this->v = obj.v;
}
Quaternion4f Quaternion4f::operator*=(Quaternion4f obj)
{
    *this = *this * obj;
    return *this;
}

Quaternion4f Quaternion4f::getConjugate()
{
    Quaternion4f ret;
    ret.w = this->w;
    ret.v = -(this->v);
    return ret;
}

Vector3f Quaternion4f::rotate(Vector3f p, Vector3f v, float angle)
{
    Quaternion4f qP = Quaternion4f(p);
    Quaternion4f qR = Quaternion4f(v, angle);
    return (qR.getConjugate() * qP * qR).v;
}

void Quaternion4f::callMe()
{
    printf("%4f\t%4f\t%4f\t%4f\n", this->w, this->v.x, this->v.y, this->v.z);
}