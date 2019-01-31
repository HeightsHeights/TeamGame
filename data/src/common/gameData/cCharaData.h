#pragma once

#include "../../common/math/vector/vector3f.h"
#include "../../common/object/transform.h"

  typedef enum {
    HAND_RIGHT = 0,
    HAND_LEFT = 1,
    HAND_NUMBER = 2,
  } HAND_ID;

class CCharaData
{
private:
public:
  CCharaData();
  unsigned int hp;
  unsigned int spawingTime;
  Transform initTransform;
  Transform transform;

  Vector3f lookingDirection;
};