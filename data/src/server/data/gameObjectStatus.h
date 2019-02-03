#pragma once

#include "../../common/gameData/cObjectData.h"
#include "../../common/object/transform.h"
#include "../collider/collider.h"
#include <iostream>

#define GRAVITY Vector3f(0.0f, -0.004f, 0.0f)

typedef enum {
  ITEM_STATE_NULL = 0,
  ITEM_STATE_IS_THROWN = 1,
  ITEM_STATE_COLLISION = 2,
  ITEM_STATE_NUMBER = 3,
} ITEM_STATE;

class GameObjectStatus
{
private:
  bool checkGround(GameObjectStatus *GameObjectStatus);
  bool checkWall();
  bool checkChara();

public:
  bool exist;
  bool isUpdated;
  ITEM_STATE state;

  OBJECT_ID objectId;

  Transform initTransform;
  Transform transform;

  Vector3f speed;
  Vector3f accel;

  Collider collider;

  GameObjectStatus();
  GameObjectStatus(OBJECT_ID id, Transform *transform, Collider *collider);

  void move();

  void killObject();
  void clearTransform();
  CObjectData getDataForClient();
};
