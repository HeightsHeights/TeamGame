#pragma once

#include "../../../common/math/random/random.h"
#include "../../../common/math/ringCounter/ringCounter.h"
#include "../../data/gameObjectStatus.h"

class ItemSpawner
{
private:
  static int currentItemNum;
  RingCounter counter;
  GameObjectStatus *dynamicGameObjects;

  void spawnItem();
  void spawnBomb();
  void spawnJewel();

public:
  ItemSpawner();
  ItemSpawner(GameObjectStatus *dynamicGameObjects);

  void update();
};