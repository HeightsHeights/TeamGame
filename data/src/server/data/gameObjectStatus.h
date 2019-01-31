#pragma once

#include "../../common/gameData/cObjectData.h"
#include "../../common/object/transform.h"
#include "../collider/collider.h"
#include <iostream>

class GameObjectStatus
{
private:
public:
  Transform initTransform;
  Transform transform;

  Vector3f speed;
  Vector3f accel;

  OBJECT_ID objectId;

  bool haveCollider;
  Collider collider;

  GameObjectStatus();
  GameObjectStatus(Transform *transform, Collider *collider);

  void clearTransform();
  CObjectData getDataForClient();
};
