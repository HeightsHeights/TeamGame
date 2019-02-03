#pragma once

#include "../math/vector/vector3f.h"
#include "../math/ringCounter/ringCounter.h"
#include "./effectId.h"
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