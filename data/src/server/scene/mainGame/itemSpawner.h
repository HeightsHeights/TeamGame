#pragma once

#include "../../../common/math/random/random.h"
#include "../../../common/math/ringCounter/ringCounter.h"
#include "../../data/gameObjectStatus.h"

#define ITEM_MAX MAX_DYNAMIC_OBJECTS - 15
#define ITEM_RATIO_BOMB 90
#define POSITION_TABLE_NUM 30

class ItemSpawner
{
private:
  RingCounter counter;
  Random random;
  GameObjectStatus *dynamicGameObjects;

  void spawnItem();
  GameObjectStatus spawnBomb(int tableNum);
  GameObjectStatus spawnJewel(int tableNum);

public:
  static int currentItemNum;
  ItemSpawner();
  ItemSpawner(GameObjectStatus *dynamicGameObjects);

  void update();
};