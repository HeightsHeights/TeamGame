#include "./obb.h"

#include "./sphere.h"

Sphere::Sphere()
{
}
Sphere::Sphere(Vector3f center, float radius)
{
    this->center = center;
    this->radius = radius;
}

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