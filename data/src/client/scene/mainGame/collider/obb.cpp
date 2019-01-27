#include "./obb.h"
#include "./sphere.h"
#include <math.h>

bool Obb::isCollision(Obb other)
{
    Vector3f NAe1 = this->normalDirect[0], Ae1 = NAe1 * this->length[0];
    Vector3f NAe2 = this->normalDirect[1], Ae2 = NAe2 * this->length[1];
    Vector3f NAe3 = this->normalDirect[2], Ae3 = NAe3 * this->length[2];
    Vector3f NBe1 = other.normalDirect[0], Be1 = NBe1 * other.length[0];
    Vector3f NBe2 = other.normalDirect[1], Be2 = NBe2 * other.length[1];
    Vector3f NBe3 = other.normalDirect[2], Be3 = NBe3 * other.length[2];
    Vector3f Interval = this->center - other.center;

    // 分離軸 : Ae1
    float rA = Ae1.magnitude();
    float rB = getLenSegOnSeparateAxis(NAe1, Be1, Be2, Be3);
    float L = fabs(Vector3f::dot(Interval, NAe1));
    if (L > rA + rB)
        return false; // 衝突していない

    // 分離軸 : Ae2
    rA = Ae2.magnitude();
    rB = getLenSegOnSeparateAxis(NAe2, Be1, Be2, Be3);
    L = fabs(Vector3f::dot(Interval, NAe2));
    if (L > rA + rB)
        return false;

    // 分離軸 : Ae3
    rA = Ae3.magnitude();
    rB = getLenSegOnSeparateAxis(NAe3, Be1, Be2, Be3);
    L = fabs(Vector3f::dot(Interval, NAe3));
    if (L > rA + rB)
        return false;

    // 分離軸 : Be1
    rA = getLenSegOnSeparateAxis(NBe1, Ae1, Ae2, Ae3);
    rB = Be1.magnitude();
    L = fabs(Vector3f::dot(Interval, NBe1));
    if (L > rA + rB)
        return false;

    // 分離軸 : Be2
    rA = getLenSegOnSeparateAxis(NBe2, Ae1, Ae2, Ae3);
    rB = Be2.magnitude();
    L = fabs(Vector3f::dot(Interval, NBe2));
    if (L > rA + rB)
        return false;

    // 分離軸 : Be3
    rA = getLenSegOnSeparateAxis(NBe3, Ae1, Ae2, Ae3);
    rB = Be3.magnitude();
    L = fabs(Vector3f::dot(Interval, NBe3));
    if (L > rA + rB)
        return false;

    // 分離軸 : C11
    Vector3f Cross;
    Cross = Vector3f::cross(NAe1, NBe1);
    rA = getLenSegOnSeparateAxis(Cross, Ae2, Ae3);
    rB = getLenSegOnSeparateAxis(Cross, Be2, Be3);
    L = fabs(Vector3f::dot(Interval, Cross));
    if (L > rA + rB)
        return false;

    // 分離軸 : C12
    Cross = Vector3f::cross(NAe1, NBe2);
    rA = getLenSegOnSeparateAxis(Cross, Ae2, Ae3);
    rB = getLenSegOnSeparateAxis(Cross, Be1, Be3);
    L = fabs(Vector3f::dot(Interval, Cross));
    if (L > rA + rB)
        return false;

    // 分離軸 : C13
    Cross = Vector3f::cross(NAe1, NBe3);
    rA = getLenSegOnSeparateAxis(Cross, Ae2, Ae3);
    rB = getLenSegOnSeparateAxis(Cross, Be1, Be2);
    L = fabs(Vector3f::dot(Interval, Cross));
    if (L > rA + rB)
        return false;

    // 分離軸 : C21
    Cross = Vector3f::cross(NAe2, NBe1);
    rA = getLenSegOnSeparateAxis(Cross, Ae1, Ae3);
    rB = getLenSegOnSeparateAxis(Cross, Be2, Be3);
    L = fabs(Vector3f::dot(Interval, Cross));
    if (L > rA + rB)
        return false;

    // 分離軸 : C22
    Cross = Vector3f::cross(NAe2, NBe2);
    rA = getLenSegOnSeparateAxis(Cross, Ae1, Ae3);
    rB = getLenSegOnSeparateAxis(Cross, Be1, Be3);
    L = fabs(Vector3f::dot(Interval, Cross));
    if (L > rA + rB)
        return false;

    // 分離軸 : C23
    Cross = Vector3f::cross(NAe2, NBe3);
    rA = getLenSegOnSeparateAxis(Cross, Ae1, Ae3);
    rB = getLenSegOnSeparateAxis(Cross, Be1, Be2);
    L = fabs(Vector3f::dot(Interval, Cross));
    if (L > rA + rB)
        return false;

    // 分離軸 : C31
    Cross = Vector3f::cross(NAe3, NBe1);
    rA = getLenSegOnSeparateAxis(Cross, Ae1, Ae2);
    rB = getLenSegOnSeparateAxis(Cross, Be2, Be3);
    L = fabs(Vector3f::dot(Interval, Cross));
    if (L > rA + rB)
        return false;

    // 分離軸 : C32
    Cross = Vector3f::cross(NAe3, NBe2);
    rA = getLenSegOnSeparateAxis(Cross, Ae1, Ae2);
    rB = getLenSegOnSeparateAxis(Cross, Be1, Be3);
    L = fabs(Vector3f::dot(Interval, Cross));
    if (L > rA + rB)
        return false;

    // 分離軸 : C33
    Cross = Vector3f::cross(NAe3, NBe3);
    rA = getLenSegOnSeparateAxis(Cross, Ae1, Ae2);
    rB = getLenSegOnSeparateAxis(Cross, Be1, Be2);
    L = fabs(Vector3f::dot(Interval, Cross));
    if (L > rA + rB)
        return false;

    // 分離平面が存在しないので「衝突している」
    return true;
}

bool Obb::isCollision(Sphere sphere)
{
    if (getLenObb2Point(sphere.center) <= sphere.radius)
    {
        return true;
    }
    return false;
}
float Obb::getLenObb2Point(Vector3f point)
{
    Vector3f retV(0, 0, 0);
    for (int i = 0; i < 3; i++)
    {
        float len = this->length[i];
        if (len <= 0)
        {
            continue;
        }
        float s = Vector3f::dot((point - this->center), this->normalDirect[i]) / len;

        s = fabs(s);
        if (s > 1)
        {
            retV += this->normalDirect[i] * ((1 - s) * len);
        }
    }

    return retV.magnitude();
}

float Obb::getLenSegOnSeparateAxis(Vector3f Sep, Vector3f e1, Vector3f e2, Vector3f e3)
{
    return getLenSegOnSeparateAxis(Sep, e1, e2) + fabs(Vector3f::dot(Sep, e3));
}
float Obb::getLenSegOnSeparateAxis(Vector3f Sep, Vector3f e1, Vector3f e2)
{
    float r1 = fabs(Vector3f::dot(Sep, e1));
    float r2 = fabs(Vector3f::dot(Sep, e2));
    return r1 + r2;
}
