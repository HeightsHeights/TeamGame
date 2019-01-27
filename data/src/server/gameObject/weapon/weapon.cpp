#include "./weapon.h"
#include <iostream>

bool Weapon::initable = true;

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
