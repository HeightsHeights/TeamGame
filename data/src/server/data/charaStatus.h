#pragma once

#include "./gameObjectStatus.h"
#include "../../common/gameData/cCharaData.h"
#include "../../common/object/transform.h"
#include "../collider/collider.h"

#define MAX_CHARA_HP 100

class CharaStatus
{
private:
  GameObjectStatus *mainBody;
  GameObjectStatus *hands[HAND_NUMBER];

  GameObjectStatus *weapon;

public:
  CharaStatus();
  CharaStatus(Transform *transform);

  bool isAlive;
  unsigned int hp;
  unsigned int spawingTime;

  Transform initTransform;
  Transform transform;
  Vector3f lookingDirection;

  float speedValue;
  Vector3f speed;
  Vector3f accel;

  void clearTransform();
  CCharaData getDataForClient();
};