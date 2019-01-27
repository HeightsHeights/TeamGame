#pragma once

#ifndef _COLLIDER_S
#define _COLLIDER_S

class Obb;

#include "../../common/math/vector/vectorSet.h"

class Sphere
{
private:
public:
  Vector3f center;
  float radius;

  Sphere();
  Sphere(Vector3f center, float radius);

  bool isCollision(Obb obb);
  bool isCollision(Sphere sphere);
};

#endif