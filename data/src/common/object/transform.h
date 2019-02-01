#pragma once

#include "../math/vector/vector3f.h"

class Transform
{
private:
public:
  Vector3f position;
  Vector3f rotation;
  Vector3f scale;

  Transform();
  Transform(Vector3f position, Vector3f rotation, Vector3f scale);
};