#include "./objectController.h"

ObjectController::ObjectController()
{
}
ObjectController::ObjectController(GameObjectStatus *staticObjects)
{
    this->staticObjects = staticObjects;
}
bool ObjectController::checkGround(Collider collider)
{
    return Collider::isCollision(collider, staticObjects[SOBJECT_TILE].collider);
}
bool ObjectController::checkWall(Collider collider)
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
bool ObjectController::checkChara(Collider collider)
{
}

GameObjectStatus ObjectController::moveObject(GameObjectStatus object)
{
    //当たり判定を動かす
    Collider tmpCollider = object.collider;

    //足元を見る
    if (!checkGround(tmpCollider))
    {
        //落ちる
        object.accel = GRAVITY;
        //落下
        if (object.transform.position.y < -20)
        {
            object.killObject();
        }
    }
    else
    {
        object.speed.y = 0;
        if (object.speed.magnitude() < 0.01f)
        {
            object.speed = Vector3f_ZERO;
            object.accel = Vector3f_ZERO;
        }
        else
        {
            object.accel = -object.speed.normalize() * 0.003f;
        }
    }
    //壁を確認
    tmpCollider.move(object.speed);
    if (checkWall(tmpCollider))
    {
        //移動可能なら更新
        object.speed = Vector3f(0.0f, object.speed.y, 0.0f);
    }
    object.transform.position += object.speed;
    object.collider = tmpCollider;
    object.isUpdated = true;
    object.speed += object.accel;
    return object;
}