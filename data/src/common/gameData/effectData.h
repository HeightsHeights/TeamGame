#pragma once

#define MAX_EFFECT 30

#include "../math/vector/vector3f.h"
#include "../math/ringCounter/ringCounter.h"
#include "./effectId.h"
class EffectData
{
private:
  EFFECT_ID id;
  unsigned int maxSpriteNum;
  unsigned int currentSpriteNum;

  RingCounter counter;

public:
  EffectData();
  EffectData(EFFECT_ID id, Vector3f position, unsigned int maxSpriteNum, int span);

  void update();
  EFFECT_ID getId();
  unsigned int getSpriteNum();

  bool exist;
  Vector3f position;
};