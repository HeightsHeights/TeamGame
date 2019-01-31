#pragma once

#include <vector>
#include "./obb.h"
#include "./sphere.h"

class Collider
{
  private:
  public:
    std::vector<Obb> obbs;
    std::vector<Sphere> spheres;
    static bool isCollision(Collider x, Collider y);
};