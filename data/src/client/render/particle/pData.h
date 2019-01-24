#pragma once

#include "../../../common/object/transform.h"
#include "../../../common/math/vector/vector3f.h"

class PData
{
private:
  int life;

public:
  Transform transform;
  Vector3f speed;
  Vector3f accel;

  PData();
  PData(Vector3f pos, Vector3f speed, Vector3f accel);
  ~PData();
};