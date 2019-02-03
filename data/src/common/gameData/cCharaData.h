#pragma once

#include "./teamId.h"
#include "../../common/math/vector/vector3f.h"
#include "../../common/object/transform.h"
#include "./cObjectData.h"

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
  TEAM_ID teamId;

  unsigned int hp;
  unsigned int spawningTime;
  bool haveWeapon;
  Transform transform;

  CObjectData mainBodyData;
  CObjectData handData[HAND_NUMBER];
  CObjectData weaponData;

  Vector3f lookingDirection;
};