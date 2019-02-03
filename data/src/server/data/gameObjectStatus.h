#pragma once

#include "../../common/gameData/cObjectData.h"
#include "../../common/object/transform.h"
#include "../collider/collider.h"
#include <iostream>

class GameObjectStatus
{
private:
public:
  bool exist;
  bool isUpdated;
  OBJECT_ID objectId;

  Transform initTransform;
  Transform transform;

  Vector3f speed;
  Vector3f accel;

  Collider collider;

  GameObjectStatus();
  GameObjectStatus(OBJECT_ID id, Transform *transform, Collider *collider);

  void killObject();
  void clearTransform();
  CObjectData getDataForClient();
};
