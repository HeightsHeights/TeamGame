#pragma once

#include "../gameObject.h"
#include "../weapon/weapon.h"

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

  Weapon *weapon;

  Vector3f lookingDirection;

  void lookatDir(Vector3f direction);
  void weaponThrow(int time);
  void weaponSodo(int time);
  void weaponAx(int time);
  void weaponBamboo(int time);
  void Cancel();

public:
  typedef enum {
    MOTION_NULL = 0,
    MOTION_ATTACL = 1,
    MOTION_THROW = 2,
    MOTION_NUMBER = 3,
  } MOTION_ID;

  Transform transform;
  float speed;

  Character();
  Character(const std::string dirPath, const std::string fileName, Transform *transform);

  void move(Vector3f moveDirection);
  void motion(MOTION_ID id, int time);
  void draw();
};