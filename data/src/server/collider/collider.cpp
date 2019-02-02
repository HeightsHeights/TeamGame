
#include "./collider.h"

Collider::Collider()
{
}
Collider::Collider(Obb obb)
{
    obbs.push_back(obb);
}
Collider::Collider(Sphere sphere)
{
    spheres.push_back(sphere);
}

bool Collider::isCollision(Collider x, Collider y)
{
    for (int i = 0; i < x.obbs.size(); i++)
    {
        for (int j = 0; j < y.obbs.size(); j++)
        {
            if (x.obbs[i].isCollision(y.obbs[j]))
            {
                return true;
            }
        }
        for (int j = 0; j < y.spheres.size(); j++)
        {
            if (x.obbs[i].isCollision(y.spheres[j]))
            {
                return true;
            }
        }
    }
    for (int i = 0; i < x.spheres.size(); i++)
    {
        for (int j = 0; j < y.obbs.size(); j++)
        {
            if (x.spheres[i].isCollision(y.obbs[j]))
            {
                return true;
            }
        }
        for (int j = 0; j < y.spheres.size(); j++)
        {
            if (x.spheres[i].isCollision(y.spheres[j]))
            {
                return true;
            }
        }
    }
    return false;
}
void Collider::move(Vector3f moveDir)
{
    for (int i = 0; i < this->obbs.size(); i++)
    {
        this->obbs[i].center += moveDir;
    }
    for (int i = 0; i < this->spheres.size(); i++)
    {
        this->spheres[i].center += moveDir;
    }
}

void Collider::setPos(Vector3f pos)
{
    for (int i = 0; i < this->obbs.size(); i++)
    {
        this->obbs[i].center = pos;
    }
    for (int i = 0; i < this->spheres.size(); i++)
    {
        this->spheres[i].center = pos;
    }
}