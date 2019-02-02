#include "./charaStatus.h"
#include <iostream>

#define SPAWNING_RATIO 300

GameObjectStatus *CharaStatus::staticObjects;

CharaStatus::CharaStatus()
{
}
CharaStatus::CharaStatus(TEAM_ID id, Transform *transform)
{
    this->teamId = id;
    this->hp = MAX_CHARA_HP;
    this->spawningTime = 0;
    this->speedValue = 0.1f;

    if (transform == NULL)
    {
        this->transform = Transform();
    }
    else
    {
        this->transform = *transform;
    }

    Collider mainCollider(Obb(this->transform.position + Vector3f(0.0f, 10.0f, 0.0f), Touple3f(3.0f, 10.0f, 3.0f)));
    mainBody = new GameObjectStatus(NULL, &mainCollider);

    mainBody->objectId = (id == TEAM_MUSH) ? OBJECT_MUSH : OBJECT_BAMBOO;

    float handSize = 1.5f;
    Vector3f handPos[HAND_NUMBER] = {
        Vector3f(2.5f, 1.5f, 0.0f),
        Vector3f(-2.5f, 1.5f, 0.0f),
    };

    Transform handInitTramsform[HAND_NUMBER] = {
        Transform(handPos[HAND_RIGHT], Vector3f_ZERO, Vector3f(1.0f, 1.0f, 1.0f) * handSize),
        Transform(handPos[HAND_LEFT], Vector3f_ZERO, Vector3f(1.0f, 1.0f, 1.0f) * handSize),
    };
    for (int i = HAND_RIGHT; i < HAND_NUMBER; i++)
    {
        Collider handCollider(Sphere(handPos[HAND_NUMBER], handSize));
        hands[i] = new GameObjectStatus(&handInitTramsform[i], &handCollider);
        hands[i]->objectId = OBJECT_CHARA_HAND;
    }

    lookingDirection = (id == TEAM_MUSH) ? Vector3f(1.0f, 0.0f, 0.0f) : Vector3f(-1.0f, 0.0f, 0.0f);
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

    if (!checkGround(tmpCollider))
    {
        transform.position.y -= 0.1;
        this->mainBody->collider.move(Vector3f(0.0f, -0.3f, 0.0f));
        if (transform.position.y < -20 && this->hp != 0)
        {
            this->hp = 0;
            this->spawningTime = 10 * SPAWNING_RATIO - 1;
        }
    }
    else
    {
        if (!checkWall(tmpCollider))
        {
            //大丈夫なら更新
            transform.position += moveDir * speedValue;
            this->mainBody->collider = tmpCollider;
            if (moveDir != Vector3f_ZERO)
            {
                lookingDirection = moveDir.normalize();
            }
        }
    }
    // transform.position += moveDir * speedValue;
}
void CharaStatus::setPos(Vector3f pos)
{
    this->transform.position = pos;
    this->mainBody->collider.setPos(pos + Vector3f(0.0f, 10.0f, 0.0f));
}
bool CharaStatus::checkGround(Collider collider)
{
    return Collider::isCollision(collider, staticObjects[SOBJECT_TILE].collider);
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
    ret.teamId = this->teamId;
    ret.hp = this->hp;
    ret.spawningTime = this->spawningTime / SPAWNING_RATIO;
    ret.transform = this->transform;
    ret.lookingDirection = this->lookingDirection;

    ret.mainBodyData = this->mainBody->getDataForClient();
    for (int i = 0; i < HAND_NUMBER; i++)
    {
        ret.handData[i] = this->hands[i]->getDataForClient();
    }

    return ret;
}