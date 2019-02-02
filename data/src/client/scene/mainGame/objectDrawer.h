#pragma once

#include "../../render/objRawModel/objRawModel.h"
#include "../../../common/gameData/cCharaData.h"

class ObjectDrawer
{
private:
  ObjRawModel **pObjects;

public:
  ObjectDrawer();
  ObjectDrawer(ObjRawModel **pObjects);

  void lookatDir(Vector3f direction);
  void drawChara(CCharaData chara);
  void drawObject(CObjectData object);
  void drawCollider(CColliderData collider);
};