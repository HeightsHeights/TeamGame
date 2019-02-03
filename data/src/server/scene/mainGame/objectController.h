#pragma once

#include "../../data/gameObjectStatus.h"
#include "../../data/charaStatus.h"
#include "./itemSpawner.h"

class ObjectController
{
private:
  GameObjectStatus *staticObjects;

  bool checkGround(Collider collider);
  bool checkWall(Collider collider);

public:
  ObjectController();
  ObjectController(GameObjectStatus *staticObjects);
  GameObjectStatus moveObject(GameObjectStatus object);
  bool checkChara(GameObjectStatus object);
};
