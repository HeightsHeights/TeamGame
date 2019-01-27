#include "./weapon.h"

#include "../render/objRawModel/objModelLoader.h"

bool Weapon::initable;
ObjRawModel *Weapon::weaponsList[WEAPON_NUMBER];

Weapon::Weapon()
{
}
Weapon::Weapon(const std::string dirPath, const std::string fileName, Transform *transform)
{
    if (transform == NULL)
    {
        this->initTransform.position = this->transform.position = Vector3f_ZERO;
        this->initTransform.rotation = this->transform.rotation = Vector3f_ZERO;
        this->initTransform.scale = this->transform.scale = Vector3f(1.0f, 1.0f, 1.0f);
    }
    else
    {
        this->initTransform.position = this->transform.position = transform->position;
        this->initTransform.rotation = this->transform.rotation = transform->rotation;
        this->initTransform.scale = this->transform.scale = transform->scale;
    }

    // model = ObjModelLoader().load(dirPath, fileName);
    // 読み込み書いて
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