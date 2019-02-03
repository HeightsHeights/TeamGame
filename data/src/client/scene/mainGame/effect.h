#pragma once

#include "../../../common/math/vector/vector3f.h"
#include "../../../common/math/ringCounter/ringCounter.h"
#include "../../../common/gameData/effectId.h"
class Effect
{
private:
  EFFECT_ID id;
  unsigned int maxSpriteNum;
  unsigned int currentSpriteNum;

  RingCounter counter;

public:
  Effect();
  Effect(EFFECT_ID id, Vector3f position, unsigned int maxSpriteNum, int span);

  void update();
  EFFECT_ID getId();
  unsigned int getSpriteNum();

  bool exist;
  Vector3f position;
};