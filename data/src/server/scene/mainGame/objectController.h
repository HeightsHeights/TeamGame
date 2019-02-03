#pragma once

#include "../../data/gameObjectStatus.h"
#include "../../data/charaStatus.h"
#include "./itemSpawner.h"

class ObjectController
{
private:
  GameObjectStatus *staticObjects;
  CharaStatus *chara;

  bool checkGround(Collider collider);
  bool checkWall(Collider collider);
  bool checkChara(Collider collider);

public:
  ObjectController();
  ObjectController(GameObjectStatus *staticObjects, CharaStatus *chara);
  GameObjectStatus moveObject(GameObjectStatus object);
};
