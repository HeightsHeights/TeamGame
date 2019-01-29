#pragma once

#include "../../common/math/vector/vector3f.h"
#include "../../common/object/transform.h"

class CPlayerData
{
  private:
  public:
    bool isAlive;
    unsigned int hp;
    unsigned int spawingTime;
    Transform initTransform;
    Transform transform;

    Vector3f lookingDirection;
};