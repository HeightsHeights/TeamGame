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

    mainBody = new GameObjectStatus(NULL, NULL);
    Transform handInitTramsform[HAND_NUMBER] = {
        Transform(Vector3f(1.5f, 1.5f, 0.0f), Vector3f_ZERO, Vector3f(1.0f, 1.0f, 1.0f)),
        Transform(Vector3f(-1.5f, 1.5f, 0.0f), Vector3f_ZERO, Vector3f(1.0f, 1.0f, 1.0f)),
    };
    for (int i = HAND_RIGHT; i < HAND_NUMBER; i++)
    {
        hands[i] = new GameObjectStatus(&handInitTramsform[i], NULL);
    }

    lookingDirection = Vector3f(1.0f, 0.0f, 0.0f);
    weapon = NULL;
}

CCharaData CharaStatus::getDataForClient()
{
}