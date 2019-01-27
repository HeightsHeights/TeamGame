#include "./weapon.h"

#include "../render/objRawModel/objModelLoader.h"

bool Weapon::initable = true;
ObjRawModel *Weapon::weaponsList[WEAPON_NUMBER];

Weapon::Weapon()
{
}
Weapon::Weapon(WEAPON_ID id, Transform *transform)
{
    if (transform == NULL)
    {
        this->transform = Transform();
    }
    else
    {
        this->transform = *transform;
    }
    this->initTransform = this->transform;

    if (initable)
    {
        // 読み込み
    }

    this->weaponId = id;
}
