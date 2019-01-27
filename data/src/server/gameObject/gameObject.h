#pragma once

#include "../../common/object/transform.h"

class GameObject
{
private:
public:
  Transform initTransform;
  Transform transform;

  Vector3f speed;
  Vector3f accel;

  // here is collider
  bool haveCollider;

  GameObject();
  GameObject(Transform *transform);

  void clearTransform();
  bool isCollision();

protected:
};