#pragma once

#include <vector>
#include "./obb.h"
#include "./sphere.h"

class Collider
{
private:
public:
  Collider();
  Collider(Obb obb);
  Collider(Sphere sphere);

  std::vector<Obb> obbs;
  std::vector<Sphere> spheres;
  static bool isCollision(Collider x, Collider y);
  void move(Vector3f moveDir);
};