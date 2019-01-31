#pragma once

#include "../../common/gameData/cObjectData.h"
#include "../../common/object/transform.h"
#include "../collider/collider.h"

class GameObjectStatus
{
private:
public:
  Transform initTransform;
  Transform transform;

  Vector3f speed;
  Vector3f accel;

  //id

  // here is collider
  bool haveCollider;

  GameObjectStatus();
  GameObjectStatus(Transform *transform);

  void clearTransform();
};
