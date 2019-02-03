#pragma once

#include "./gameObjectStatus.h"

#include "../../common/gameData/cCharaData.h"
#include "../../common/object/transform.h"
#include "../collider/collider.h"

#define MAX_CHARA_HP 50

class CharaStatus
{
private:
  static GameObjectStatus *staticObjects;

  GameObjectStatus *mainBody;
  GameObjectStatus *hands[HAND_NUMBER];
  GameObjectStatus *weapon;

  bool checkGround(Collider collider);
  bool checkWall(Collider collider);

  void grab(GameObjectStatus *dynamicObjects);
  void weaponThrow(GameObjectStatus *dynamicObjects);

public:
  CharaStatus();
  CharaStatus(TEAM_ID id, Transform *transform);

  TEAM_ID teamId;

  unsigned int hp;
  unsigned int spawningTime;

  Transform transform;
  Vector3f lookingDirection;

  float throwingSpeed;
  float speedValue;
  Vector3f speed;
  Vector3f accel;

  bool atkMode;

  static bool init(GameObjectStatus *staticObjects);

  void move(Vector3f moveDir);
  void setPos(Vector3f pos);
  bool attack();
  // void weaponThrow(bool haveWeapon);
  void weaponEvent(GameObjectStatus *dynamicObjects);
  bool damage(unsigned int damageValue, Collider collider);
  void died();

  CCharaData getDataForClient();
};