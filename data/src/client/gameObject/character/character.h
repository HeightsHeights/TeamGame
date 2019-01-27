#pragma once

#include "../gameObject.h"

class Character
{
private:
  typedef enum {
    HAND_RIGHT = 0,
    HAND_LEFT = 1,
    HAND_NUMBER = 2,
  } HAND_ID;

  GameObject *mainBody;
  GameObject *hands[HAND_NUMBER];

  GameObject *weaponsList;
  GameObject *weapon;

  Vector3f lookingDirection;

  void lookatDir(Vector3f direction);

public:
  typedef enum {
    ATTACK_HAVENOTHING = 0,
    ATTACK_SWORD = 1,
    ATTACK_BARDICHEWITHMATERIAL = 2,
    ATTACK_THLOW = 3,
  } ATTACK_ID;

  Transform transform;
  float speed;

  Character();
  Character(const std::string dirPath, const std::string fileName, Transform *transform);

  void move(Vector3f moveDirection);
  void motion(ATTACK_ID id, int time);
  void draw();
};