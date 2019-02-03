#include "objectDrawer.h"

ObjectDrawer::ObjectDrawer()
{
}
ObjectDrawer::ObjectDrawer(ObjRawModel **pObjects)
{
    this->pObjects = pObjects;
}

void ObjectDrawer::drawChara(CCharaData chara)
{
    glPushMatrix();
    Transform *pCharaTransform = &chara.transform;
    glScalef(pCharaTransform->scale.x, pCharaTransform->scale.y, pCharaTransform->scale.z);
    glTranslatef(pCharaTransform->position.x, pCharaTransform->position.y, pCharaTransform->position.z);
    lookatDir(chara.lookingDirection);

    drawObject(chara.mainBodyData);

    //手
    for (int i = 0; i < HAND_NUMBER; i++)
    {
        drawObject(chara.handData[i]);
    }

    // weapon
    if (chara.haveWeapon)
    {
        drawObject(chara.weaponData);
    }

    glPopMatrix();
}

void ObjectDrawer::lookatDir(Vector3f direction)
{
    direction.y = 0;

    Vector3f vecY = Vector3f(0, 1, 0);
    Vector3f vecZ = Vector3f(0, 0, 1);

    float theta = direction.betweenAngleDegree(vecZ);
    if (Vector3f::cross(vecZ, direction).y < 0)
    {
        theta *= -1;
    }
    glRotated(theta, vecY.x, vecY.y, vecY.z);
}
void ObjectDrawer::drawObject(CObjectData object)
{
    if (!object.exist)
    {
        return;
    }
    glPushMatrix();
    Transform *pObjectTransform = &object.transform;
    glTranslatef(pObjectTransform->position.x, pObjectTransform->position.y, pObjectTransform->position.z);
    glScalef(pObjectTransform->scale.x, pObjectTransform->scale.y, pObjectTransform->scale.z);
    pObjects[object.objectId]->draw();
    glPopMatrix();
}

void ObjectDrawer::drawCollider(CColliderData collider)
{
    glPushMatrix();
    Transform *pColliderTransform = &collider.transform;
    glTranslatef(pColliderTransform->position.x, pColliderTransform->position.y, pColliderTransform->position.z);
    glScalef(pColliderTransform->scale.x, pColliderTransform->scale.y, pColliderTransform->scale.z);

    OBJECT_ID id = (collider.id == COLLIDER_OBB) ? OBJECT_DEBUG_OBB : OBJECT_DEBUG_SPHERE;
    pObjects[id]->draw();
    glPopMatrix();
}
void ObjectDrawer::drawEffect(EffectData effect, GuiSprite *sprite)
{
    sprite[effect.getId()].draw(effect.getSpriteNum(), NULL);
}