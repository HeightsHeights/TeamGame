#pragma once

#include "../../../common/math/vector/vector3f.h"

class PData
{
private:
  unsigned int life;

public:
  Vector3f pos;
  Vector3f speed;
  Vector3f accel;

  PData();
  void damage() { life--; }
};