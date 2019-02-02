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
    glScalef(chara.transform.scale.x, chara.transform.scale.y, chara.transform.scale.z);
    glTranslatef(chara.transform.position.x, chara.transform.position.y, chara.transform.position.z);
    lookatDir(chara.lookingDirection);

    glPushMatrix();
    Transform *pMainBodyTransform = &chara.mainBodyData.transform;
    glTranslatef(pMainBodyTransform->position.x, pMainBodyTransform->position.y, pMainBodyTransform->position.z);
    glScalef(pMainBodyTransform->scale.x, pMainBodyTransform->scale.y, pMainBodyTransform->scale.z);
    pObjects[chara.mainBodyData.objectId]->draw();
    glPopMatrix();

    drawObject(chara.mainBodyData);

    for (int i = 0; i < HAND_NUMBER; i++)
    {
        drawObject(chara.handData[i]);

        // glPushMatrix();
        // Transform *pHandTransform = &chara.handData[i].transform;
        // glTranslatef(pHandTransform->position.x, pHandTransform->position.y, pHandTransform->position.z);
        // glScalef(pHandTransform->scale.x, pHandTransform->scale.y, pHandTransform->scale.z);
        // pObjects[chara.handData[i].objectId]->draw();
        // glPopMatrix();
    }

    // weapon

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