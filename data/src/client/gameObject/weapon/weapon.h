#pragma once

#include "../render/objRawModel/objRawModel.h"
#include "../../../common/object/transform.h"

class Weapon
{
  public:
    typedef enum {
        WEAPON_SWORD = 0,
        WEAPON_AX = 1,
        WEAPON_SPEAR = 2,
        WEAPON_NUMBER = 3,
    } WEAPON_ID;

  private:
    static bool initable;
    static ObjRawModel *weaponsList[WEAPON_NUMBER];

  public:
    Transform initTransform;
    Transform transform;
    Vector3f speed;
    Vector3f accel;

    WEAPON_ID weaponId;

    Weapon();
    Weapon(const std::string dirPath, const std::string fileName, Transform *transform);

    void move(Vector3f moveDirection);
    void draw();
};