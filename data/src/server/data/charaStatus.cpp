#include "./charaStatus.h"
#include <iostream>

CharaStatus::CharaStatus()
{
}
CharaStatus::CharaStatus(Transform *transform)
{
    speedValue = 0.1f;

    if (transform == NULL)
    {
        this->transform = Transform();
    }
    else
    {
        this->transform = *transform;
    }

    Collider mainCollider(Obb(Vector3f(0, 10.0f, 0), Touple3f(3.0f, 10.0f, 3.0f)));
    mainBody = new GameObjectStatus(NULL, &mainCollider);

    float handSize = 1.5f;
    Vector3f handPos[HAND_NUMBER] = {
        Vector3f(1.5f, 1.5f, 0.0f),
        Vector3f(-1.5f, 1.5f, 0.0f),
    };

    Transform handInitTramsform[HAND_NUMBER] = {
        Transform(handPos[HAND_RIGHT], Vector3f_ZERO, Vector3f(1.0f, 1.0f, 1.0f) * handSize),
        Transform(handPos[HAND_RIGHT], Vector3f_ZERO, Vector3f(1.0f, 1.0f, 1.0f) * handSize),
    };
    for (int i = HAND_RIGHT; i < HAND_NUMBER; i++)
    {
        Collider handCollider(Sphere(handPos[HAND_NUMBER], handSize));
        hands[i] = new GameObjectStatus(&handInitTramsform[i], &handCollider);
    }

    lookingDirection = Vector3f(1.0f, 0.0f, 0.0f);
    weapon = NULL;
}

CCharaData CharaStatus::getDataForClient()
{
    return CCharaData();
}