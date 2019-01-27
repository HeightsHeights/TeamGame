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

void Weapon::draw()
{
    glPushMatrix();

    glScalef(transform.scale.x, transform.scale.y, transform.scale.z);
    glRotatef(transform.rotation.y, 0.0f, 1.0f, 0.0f);
    glTranslatef(transform.position.x, transform.position.y, transform.position.z);

    weaponsList[weaponId]->draw();
    glPopMatrix();
}