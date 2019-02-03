#include "./itemSpawner.h"

int ItemSpawner::currentItemNum = 0;

Vector3f positionTable[POSITION_TABLE_NUM] = {
    Vector3f(20.0f, 0.0f, 0.0f),
    Vector3f(-20.0f, 0.0f, 0.0f),
    Vector3f(40.0f, 0.0f, 0.0f),
    Vector3f(-40.0f, 0.0f, 0.0f),
    Vector3f(60.0f, 0.0f, 0.0f),
    Vector3f(-60.0f, 0.0f, 0.0f),
    Vector3f(80.0f, 0.0f, 0.0f),
    Vector3f(-80.0f, 0.0f, 0.0f),
    Vector3f(100.0f, 0.0f, 0.0f),
    Vector3f(-100.0f, 0.0f, 0.0f),
};

ItemSpawner::ItemSpawner()
{
}
ItemSpawner::ItemSpawner(GameObjectStatus *dynamicGameObjects)
{
    this->dynamicGameObjects = dynamicGameObjects;
    this->counter = RingCounter(0, 0, 100);
    Random::init();
}

void ItemSpawner::update()
{
    ++counter;
    if (counter.isMax())
    {
        spawnItem();
    }
}

void ItemSpawner::spawnItem()
{
    if (currentItemNum > ITEM_MAX)
    {
        return;
    }
    int i;
    for (i = 0; i < MAX_DYNAMIC_OBJECTS; i++)
    {
        if (dynamicGameObjects[i].exist)
        {
            break;
        }
    }

    currentItemNum++;
    int tableNum = random.randIntBetween(0, POSITION_TABLE_NUM);
    int itemNum = random.randIntBetween(0, 99);
    if (itemNum < ITEM_RATIO_BOMB)
    {
        dynamicGameObjects[i] = spawnBomb(tableNum);
    }
    else
    {
        dynamicGameObjects[i] = spawnJewel(tableNum);
    }
}
GameObjectStatus ItemSpawner::spawnBomb(int tableNum)
{
    Vector3f tmpPos = positionTable[tableNum] + Vector3f(0.0f, 50.0f, 0.0f);
    Transform tmpTransform = Transform(tmpPos, Vector3f_ZERO, Vector3f(1.5f, 1.5f, 1.5f));
    Collider tmpCollider(Sphere(tmpPos, 3));
    return GameObjectStatus(OBJECT_BOMB, &tmpTransform, &tmpCollider);
}
GameObjectStatus ItemSpawner::spawnJewel(int tableNum)
{
    int num = random.randFloatBetween(0, 2);
    Vector3f tmpPos = positionTable[tableNum] + Vector3f(0.0f, 50.0f, 0.0f);
    Transform tmpTransform = Transform(tmpPos, Vector3f_ZERO, Vector3f(5.0f, 5.0f, 5.0f));
    Collider tmpCollider(Sphere(tmpPos, 4));
    return GameObjectStatus((OBJECT_ID)(OBJECT_JEWEL_R + num), &tmpTransform, &tmpCollider);
}