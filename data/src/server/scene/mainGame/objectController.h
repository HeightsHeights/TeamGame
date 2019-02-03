#pragma once

#include "../../data/gameObjectStatus.h"
#include "../../data/charaStatus.h"

class ObjectController
{
  private:
    GameObjectStatus *staticObjects;

    bool checkGround(Collider collider);
    bool checkWall(Collider collider);
    bool checkChara(Collider collider);

  public:
    ObjectController();
    ObjectController(GameObjectStatus *staticObjects);
    GameObjectStatus moveObject(GameObjectStatus object);
};
