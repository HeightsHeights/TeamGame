#pragma once

#ifndef _COLLIDER_O
#define _COLLIDER_O

class Sphere;

#include "../../common/math/vector/vectorSet.h"

class Obb
{
private:
public:
  Vector3f center;
  Vector3f normalDirect[3];
  float length[3];

  Obb();
  Obb(Vector3f center, Touple3f length);

  bool isCollision(Obb other);
  bool isCollision(Sphere sphere);
  float getLenObb2Point(Vector3f point);
  float getLenSegOnSeparateAxis(Vector3f Sep, Vector3f e1, Vector3f e2, Vector3f e3);
  float getLenSegOnSeparateAxis(Vector3f Sep, Vector3f e1, Vector3f e2);
};

#endif