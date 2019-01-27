#pragma once

#include "../gameObject.h"
#include "../../../common/object/transform.h"

class Weapon : public GameObject
{
public:
  typedef enum
  {
    WEAPON_SWORD = 0,
    WEAPON_AXE = 1,
    WEAPON_SPEAR = 2,
    WEAPON_NUMBER = 3,
  } WEAPON_ID;

private:
  static bool initable;

public:
  WEAPON_ID weaponId;

  Weapon();
  Weapon(WEAPON_ID id, Transform *transform);

  void move(Vector3f moveDirection);
};