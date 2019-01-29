#pragma once

#include "../../common/math/vector/vector3f.h"
#include "../../common/object/transform.h"

#define MAX_CHARA_HP 100

class CharaStatus
{
  private:
  public:
    CharaStatus();

    bool isAlive;
    unsigned int hp;
    unsigned int spawingTime;

    Transform initTransform;
    Transform transform;

    Vector3f speed;
    Vector3f accel;

    Vector3f lookingDirection;
};