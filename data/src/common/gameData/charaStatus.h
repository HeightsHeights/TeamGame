#pragma once

#include "../math/vector/vector3f.h"

#define MAX_CHARA_HP 100

class CharaStatus
{
  private:
  public:
    CharaStatus();

    bool isAlive;
    unsigned int hp;
};