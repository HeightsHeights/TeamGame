#pragma once

#include "../../common/object/transform.h"
#include "../render/objRawModel/objRawModel.h"

class GameObject
{
  private:
    ObjRawModel *model;

  public:
    Transform transform;
    //here is collider

    GameObject();
    GameObject(const std::string dirPath, const std::string fileName, Transform *transform);
    void draw();
};