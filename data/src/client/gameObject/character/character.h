#pragma once

#include "../gameObject.h"

class Character
{
private:
  typedef enum
  {
    HAND_RIGHT = 0,
    HAND_LEFT = 1,
    HAND_NUMBER = 2,
  } HAND_ID;

  GameObject *mainBody;
  GameObject *hands[HAND_NUMBER];

  GameObject *weapons;

public:
  Transform transform;

  Character();
  Character(const std::string dirPath, const std::string fileName, Transform *transform);

  void move();
  void draw();
};