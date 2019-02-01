#include "./charaStatus.h"
#include <iostream>

GameObjectStatus *CharaStatus::staticObjects;

CharaStatus::CharaStatus()
{
    this->hp = MAX_CHARA_HP;
    speedValue = 0.1f;

    this->transform = Transform(Vector3f(10.0f, 0, 0), Vector3f_ZERO, Vector3f(1.0f, 3.0f, 1.0f));

    Collider mainCollider(Obb(Vector3f(10.0f, 10.0f, 0), Touple3f(3.0f, 10.0f, 3.0f)));
    mainBody = new GameObjectStatus(NULL, &mainCollider);
    mainBody->objectId = OBJECT_MUSH;

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
        hands[i]->objectId = OBJECT_CHARA_HAND;
    }

    lookingDirection = Vector3f(1.0f, 0.0f, 0.0f);
    weapon = NULL;
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

    Collider mainCollider(Obb(Vector3f(0.0f, 10.0f, 0), Touple3f(3.0f, 10.0f, 3.0f)));
    mainBody = new GameObjectStatus(NULL, &mainCollider);
    mainBody->objectId = OBJECT_MUSH;

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
        hands[i]->objectId = OBJECT_CHARA_HAND;
    }

    lookingDirection = Vector3f(1.0f, 0.0f, 0.0f);
    weapon = NULL;
}

bool CharaStatus::init(GameObjectStatus *staticObjects)
{
    if (staticObjects == NULL)
    {
        return false;
    }
    CharaStatus::staticObjects = staticObjects;
    return true;
}

void CharaStatus::move(Vector3f moveDir)
{
    //当たり判定を動かす
    Collider tmpCollider = this->mainBody->collider;
    tmpCollider.move(moveDir * speedValue);
    //見る
    if (!checkWall(tmpCollider))
    {
        //大丈夫なら更新
        transform.position += moveDir * speedValue;
        this->mainBody->collider = tmpCollider;
    }
}

bool CharaStatus::checkGround(Collider collider)
{
    return true;
}
bool CharaStatus::checkWall(Collider collider)
{
    for (int i = SOBJECT_TOWER_R; i < SOBJECT_NUMBER; i++)
    {
        if (Collider::isCollision(collider, staticObjects[i].collider))
        {
            return true;
        }
    }
    return false;
}

CCharaData CharaStatus::getDataForClient()
{
    CCharaData ret;
    ret.hp = this->hp;
    ret.spawningTime = this->spawningTime;
    ret.transform = this->transform;
    ret.lookingDirection = this->lookingDirection;

    ret.mainBodyData = this->mainBody->getDataForClient();
    for (int i = 0; i < HAND_NUMBER; i++)
    {
        ret.handData[i] = this->hands[i]->getDataForClient();
    }

    return ret;
}