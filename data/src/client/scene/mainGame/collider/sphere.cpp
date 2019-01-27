#include "./obb.h"

#include "./sphere.h"

bool Sphere::isCollision(Obb obb)
{
    return obb.isCollision(*this);
}

bool Sphere::isCollision(Sphere sphere)
{
    Vector3f diffV = this->center - sphere.center;
    if (diffV.magnitudeSquared() <= this->radius + sphere.radius)
    {
        return true;
    }
    return false;
}