#include "./charaStatus.h"
#include <iostream>
#include <math.h>

#define SPAWNING_RATIO 300

GameObjectStatus *CharaStatus::staticObjects;

CharaStatus::CharaStatus()
{
}
CharaStatus::CharaStatus(TEAM_ID id, Transform *transform)
{
    this->atkMode = false;

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
    mainBody = new GameObjectStatus((id == TEAM_MUSH) ? OBJECT_MUSH : OBJECT_BAMBOO, NULL, &mainCollider);

    float handSize = 1.5f;
    Vector3f handPos[HAND_NUMBER] = {
        Vector3f(2.5f, 1.5f, 0.0f),
        Vector3f(-2.5f, 1.5f, 0.0f),
    };
    Transform handInitTramsform[HAND_NUMBER] = {
        Transform(handPos[HAND_LEFT], Vector3f_ZERO, Vector3f(1.0f, 1.0f, 1.0f) * handSize),
        Transform(handPos[HAND_RIGHT], Vector3f_ZERO, Vector3f(1.0f, 1.0f, 1.0f) * handSize),
    };
    for (int i = HAND_RIGHT; i < HAND_NUMBER; i++)
    {
        Collider handCollider(Sphere(handPos[HAND_NUMBER], handSize));
        hands[i] = new GameObjectStatus(OBJECT_CHARA_HAND, &handInitTramsform[i], &handCollider);
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

    //足元を見る
    if (!checkGround(tmpCollider))
    {
        //落ちる
        transform.position.y -= 0.1;
        this->mainBody->collider.move(Vector3f(0.0f, -0.3f, 0.0f));

        //落下死
        if (transform.position.y < -20 && this->hp != 0)
        {
            this->hp = 0;
            this->spawningTime = 10 * SPAWNING_RATIO - 1;
        }
    }
    else
    {
        //壁を確認
        tmpCollider.move(moveDir * speedValue);
        if (!checkWall(tmpCollider))
        {
            //移動可能なら更新
            transform.position += moveDir * speedValue;
            this->mainBody->collider = tmpCollider;
        }
    }
    //入力値に向きを合わせる
    if (moveDir != Vector3f_ZERO)
    {
        lookingDirection = moveDir.normalize();
    }
}
void CharaStatus::setPos(Vector3f pos)
{
    this->transform.position = pos;
    this->mainBody->collider.setPos(pos + Vector3f(0.0f, 10.0f, 0.0f));
}
void CharaStatus::weaponEvent(GameObjectStatus *dynamicObjects)
{ //武器を持っているか
    if (this->weapon == NULL)
    {
        grab(dynamicObjects);
    }
    else
    {
        weaponThrow(dynamicObjects);
    }
}
void CharaStatus::grab(GameObjectStatus *dynamicObjects)
{
    for (int i = 0; i < MAX_DYNAMIC_OBJECTS; i++)
    {
        GameObjectStatus *pObject = &dynamicObjects[i];
        //オブジェクトは存在する
        if (!pObject->exist)
        {
            continue;
        }
        //取得可能範囲内
        if (Collider::isCollision(this->mainBody->collider, pObject->collider))
        {
            //武器を更新
            pObject->killObject();
            Vector3f tmpPos = this->hands[HAND_RIGHT]->transform.position + Vector3f(0.0f, 1.0f, 0.0f);
            Transform tmpTransform = pObject->transform;
            tmpTransform.position = tmpPos;
            tmpTransform.scale /= 1.5;
            Collider tmpCollider = pObject->collider;
            tmpCollider.setPos(tmpPos);
            weapon = new GameObjectStatus(pObject->objectId, &tmpTransform, &tmpCollider);
            break;
        }
    }
}
void CharaStatus::weaponThrow(GameObjectStatus *dynamicObjects)
{
    for (int i = 0; i < MAX_DYNAMIC_OBJECTS; i++)
    {
        GameObjectStatus *pObject = &dynamicObjects[i];
        if (!pObject->exist)
        {
            Vector3f tmpPos = this->transform.position;
            Transform tmpTransform = this->weapon->transform;
            tmpTransform.position = tmpPos;
            tmpTransform.scale *= 1.5;
            Collider tmpCollider = weapon->collider;
            tmpCollider.setPos(tmpPos);
            *pObject = GameObjectStatus(weapon->objectId, &tmpTransform, &tmpCollider);
            delete weapon;
            this->weapon = NULL;
            break;
        }
    }
}
bool CharaStatus::attack()
{
    this->hands[HAND_LEFT]->speed.z = 0.5f;
    this->hands[HAND_LEFT]->transform.position += this->hands[HAND_LEFT]->speed;
    if (this->hands[HAND_LEFT]->transform.position.z > 8.0)
    {
        this->hands[HAND_LEFT]->speed.z = 0;
        this->hands[HAND_LEFT]->clearTransform();
        return false;
    }
    return true;
}

// void CharaStatus::weaponThrow(bool haveWeapon)
// {
// static int ang;
//     Collider tmpCollider = this->mainBody->collider;
// if (haveWeapon == false)
// {
//         if () //武器と拾うところの当たり判定
//     this->hands[HAND_RIGHT]->transform.position.y += 2.0f;
//     this->haveWeapon = true;
// }
// else
// {
//     this->hands[HAND_RIGHT]->transform.position += Vector3f(0.0f, (float)sin(++ang) * 2.0f / 2.0f, (float)cos(ang) * 2.0f / 2.0f); //投げる動作
//     if (ang > 15)
//     {
//         this->hands[HAND_RIGHT]->clearTransform();
//         ang = 0;
//         this->haveWeapon = false;
//     }
// }
//     return;
// }

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

    ret.haveWeapon = false;
    if (this->weapon != NULL)
    {
        ret.haveWeapon = true;
        ret.weaponData = this->weapon->getDataForClient();
    }

    return ret;
}