#pragma once

#include "../../../common/math/random/random.h"
#include "../../../common/math/ringCounter/ringCounter.h"
#include "../../data/gameObjectStatus.h"

class ItemSpawner
{
private:
  RingCounter counter;

  //table
  //
public:
  ItemSpawner();
  ItemSpawner(GameObjectStatus *dynamicGameObjects);

  void update();
  void spawnItem();
};