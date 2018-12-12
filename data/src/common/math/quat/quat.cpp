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
    this->w = 0;
    this->v = position;
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

    this->w = cosine;
    this->v = axis * sine;
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
Matrix4x4f Quaternion4f::toMatrix()
{
    Matrix4x4f ret = Matrix4x4f_IDENTITY;
    float sx = this->v.x * this->v.x;
    float sy = this->v.y * this->v.y;
    float sz = this->v.z * this->v.z;
    float cx = this->v.y * this->v.z;
    float cy = this->v.x * this->v.z;
    float cz = this->v.x * this->v.y;
    float wx = this->w * this->v.x;
    float wy = this->w * this->v.y;
    float wz = this->w * this->v.z;

    ret[Matrix4x4f_INDEX(0, 0)] = 1.0f - 2.0f * (sy + sz);
    ret[Matrix4x4f_INDEX(0, 1)] = 2.0f * (cz + wz);
    ret[Matrix4x4f_INDEX(0, 2)] = 2.0f * (cy - wy);
    ret[Matrix4x4f_INDEX(1, 0)] = 2.0f * (cz - wz);
    ret[Matrix4x4f_INDEX(1, 1)] = 1.0f - 2.0f * (sx + sz);
    ret[Matrix4x4f_INDEX(1, 2)] = 2.0f * (cx + wx);
    ret[Matrix4x4f_INDEX(2, 0)] = 2.0f * (cy + wy);
    ret[Matrix4x4f_INDEX(2, 1)] = 2.0f * (cx - wx);
    ret[Matrix4x4f_INDEX(2, 2)] = 1.0f - 2.0f * (sx + sy);
    ret[Matrix4x4f_INDEX(3, 0)] = 0.0f;
    ret[Matrix4x4f_INDEX(3, 1)] = 0.0f;
    ret[Matrix4x4f_INDEX(3, 2)] = 0.0f;
    return ret;
}
Vector3f Quaternion4f::rotate(Vector3f p, Vector3f v, float angle)
{
    Quaternion4f qP = Quaternion4f(p);
    Quaternion4f qR = Quaternion4f(v, angle);
    return (qR * qP * qR.getConjugate()).v;
}

void Quaternion4f::callMe()
{
    printf("%4f\t%4f\t%4f\t%4f\n", this->w, this->v.x, this->v.y, this->v.z);
    printf("\n\n\n");
}