#pragma once

#include "../../../common/math/vector/vector3f.h"

class PData
{
private:
public:
  Vector3f pos;
  Vector3f speed;
  Vector3f accel;

  unsigned int life;

  PData();
};