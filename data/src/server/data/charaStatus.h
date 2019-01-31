#pragma once

#include "../../common/gameData/cCharaData.h"
#include "../../common/object/transform.h"
#include "../collider/collider.h"

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

  int speedValue;
  Vector3f speed;
  Vector3f accel;

  Vector3f lookingDirection;

  CCharaData getDataForClient();
  void clearTransform();
};