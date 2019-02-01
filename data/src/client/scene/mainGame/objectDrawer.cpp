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
    // lookatDir(lookingDirection);

    glPushMatrix();
    Transform *pMainBodyTransform = &chara.mainBodyData.transform;
    glTranslatef(pMainBodyTransform->position.x, pMainBodyTransform->position.y, pMainBodyTransform->position.z);
    pObjects[chara.mainBodyData.objectId]->draw();
    glPopMatrix();

    for (int i = 0; i < HAND_NUMBER; i++)
    {
        glPushMatrix();
        Transform *pHandTransform = &chara.handData[HAND_RIGHT].transform;
        glTranslatef(pHandTransform->position.x, pHandTransform->position.y, pHandTransform->position.z);
        glScalef(pHandTransform->scale.x, pHandTransform->scale.y, pHandTransform->scale.z);
        pObjects[chara.handData[HAND_RIGHT].objectId]->draw();
        glPopMatrix();
    }

    // weapon

    glPopMatrix();
}
void ObjectDrawer::drawObject(CObjectData object)
{
    glPushMatrix();
    glTranslatef(object.transform.position.x, object.transform.position.y, object.transform.position.z);
    glScalef(object.transform.scale.x, object.transform.scale.y, object.transform.scale.z);
    pObjects[object.objectId]->draw();
    glPopMatrix();
}