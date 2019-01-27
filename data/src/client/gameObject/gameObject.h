#pragma once

#include "../../common/object/transform.h"
#include "../render/objRawModel/objRawModel.h"

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
  GameObject(const std::string dirPath, const std::string fileName, Transform *transform);

  void clearTransform();
  bool isCollision();
  void draw();

protected:
  ObjRawModel *model;
};