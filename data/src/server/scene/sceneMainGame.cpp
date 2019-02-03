#include "./sceneMainGame.h"

#include "../network/networkManager.h"
#include "../../common/network/dataBlock/dataBlock.h"
#include "../../common/controllerParam/controllerParam.h"
#include "./mainGame/objectController.h"
#include <stdio.h>

bool SceneMainGame::init()
{
    gameInitable = true;
    Collider staticColliders[] = {
        Collider(Obb(Vector3f(-7, 0, 0), Touple3f(143, 0.01f, 72))), //床
        Collider(Obb(Vector3f(-140, 20, 0), Touple3f(3, 20, 3))),    //塔
        Collider(Obb(Vector3f(125, 20, 0), Touple3f(3, 20, 3))),     //塔
        Collider(Obb(Vector3f(-100, 10, 40), Touple3f(2, 10, 20))),  //壁
        Collider(Obb(Vector3f(-65, 10, -40), Touple3f(2, 10, 20))),  //壁
        Collider(Obb(Vector3f(85, 10, -40), Touple3f(2, 10, 20))),   //壁
        Collider(Obb(Vector3f(50, 10, 40), Touple3f(2, 10, 20))),    //壁
        Collider(Obb(Vector3f(0, 10, 0), Touple3f(2, 10, 20))),      //壁
    };
    Transform staticObjectTranforms[] = {
        Transform(Vector3f(0, 0, 0), Vector3f_ZERO, Vector3f(20.0f, 1.0f, 10.0f)),              //床
        Transform(Vector3f(-140.0f, 1.0f, 0.0f), Vector3f_ZERO, Vector3f(0.03f, 0.07f, 0.03f)), //塔
        Transform(Vector3f(125.0f, 1.0f, 0.0f), Vector3f_ZERO, Vector3f(0.03f, 0.07f, 0.03f)),  //塔
        Transform(Vector3f(-100.0, 10.0, 40), Vector3f_ZERO, Vector3f(10.0f, 10.0f, 10.0f)),    //壁
        Transform(Vector3f(-65.0, 10.0, -40), Vector3f_ZERO, Vector3f(10.0f, 10.0f, 10.0f)),    //壁
        Transform(Vector3f(85.0, 10.0, -40), Vector3f_ZERO, Vector3f(10.0f, 10.0f, 10.0f)),     //壁
        Transform(Vector3f(50.0, 10.0, 40), Vector3f_ZERO, Vector3f(10.0f, 10.0f, 10.0f)),      //壁
        Transform(Vector3f(0.0, 10.0, 0.0), Vector3f_ZERO, Vector3f(10.0f, 10.0f, 10.0f)),      //壁
    };
    const OBJECT_ID ids[] = {
        OBJECT_TILE,        //床
        OBJECT_TOWER_R,     //塔
        OBJECT_TOWER_B,     //塔
        OBJECT_WALL_R,      //壁
        OBJECT_WALL_R,      //壁
        OBJECT_WALL_B,      //壁
        OBJECT_WALL_B,      //壁
        OBJECT_WALL_NORMAL, //壁
    };

    for (int i = 0; i < SOBJECT_NUMBER; i++)
    {
        staticObjectStatus[i] = GameObjectStatus(ids[i], &staticObjectTranforms[i], &staticColliders[i]);
    }
    if (!CharaStatus::init(&staticObjectStatus[0]))
    {
        fprintf(stderr, "Error --> CharaStatus::init()\n");
        return false;
    }

    for (int i = 0; i < TEAM_NUMBER; i++)
    {
        tStatus[i] = TeamStatus();
    }
    return true;
}
SCENE_ID SceneMainGame::executeCommand(int command, int pos)
{
    SCENE_ID nextScene = SI_MAIN;

    if (command == NC_SEND_CONTROLLER_PARAM)
    {
        ControllerParam *pController = &clientsData[pos].controllerParam;
        NetworkManager::recvData(pos, pController, sizeof(ControllerParam));

        if (pController->buttonDown[CT_FINISH])
        {
            DataBlock data;
            data.setCommand2DataBlock(NC_FINISH);
            NetworkManager::sendData(ALL_CLIENTS, data, data.getDataSize());
            nextScene = SI_NUMBER;
        }
    }
    return nextScene;
}
SCENE_ID SceneMainGame::dataProcessing()
{
    SCENE_ID nextScene = SI_MAIN;
    nextScene = upDate();
    sendData();
    return nextScene;
}

SCENE_ID SceneMainGame::upDate()
{
    SCENE_ID nextScene = SI_MAIN;
    if (gameInitable)
    {
        itemSpawner = ItemSpawner(&dynamicObjectStatus[0]);
        for (int i = 0; i < MAX_PLAYERS; i++)
        {
            Transform charaTransform = Transform((clientsData[i].teamId == TEAM_MUSH) ? Vector3f(-60.0f, 0.0f, 0.0f) : Vector3f(60.0f, 0.0f, 0.0f), Vector3f_ZERO, Vector3f(1.0f, 3.0f, 1.0f));
            cStatus[i] = CharaStatus(clientsData[i].teamId, &charaTransform);

            timer = 1000;
            progress = PROGRESS_WAITING;
        }
    }

    if (progress == PROGRESS_WAITING)
    {
        timer--;
        if (timer == 0)
        {
            progress = PROGRESS_GAMING;
            sendSignal(SIGNAL_NULL);
        }
        else if (timer == 300)
        {
            timer--;
            sendSignal(SIGNAL_GO);
        }
        return nextScene;
    }
    else if (progress == PROGRESS_FINISHING)
    {
        timer--;
        if (timer == 1000)
        {
            sendSignal(SIGNAL_WINNER);
        }
        else if (timer == 0)
        {
            DataBlock data;
            data.setCommand2DataBlock(NC_FINISH);
            NetworkManager::sendData(ALL_CLIENTS, data, data.getDataSize());
            nextScene = SI_NUMBER;
        }
        return nextScene;
    }

    itemSpawner.update();
    for (int i = 0; i < MAX_DYNAMIC_OBJECTS; i++)
    {
        //moving
        GameObjectStatus *pObject = &dynamicObjectStatus[i];
        if (!pObject->exist)
        {
            continue;
        }
        objectMovingProcess(i);

        if (pObject->state == ITEM_STATE_COLLISION)
        {
            if (pObject->objectId == OBJECT_BOMB)
            {

                Collider bombCollider = Collider(Sphere(pObject->transform.position, 13));
                for (int i = 0; i < MAX_PLAYERS; i++)
                {
                    if (cStatus[i].hp > 0)
                    {
                        if (cStatus[i].damage(pObject->damageValue, bombCollider))
                        {
                            sendEffect(EFFECT_DEAD, cStatus[i].transform.position);
                        }
                    }
                }

                for (int i = 0; i < TEAM_NUMBER; i++)
                {
                    if (towerDamageProcess(i, bombCollider, pObject->damageValue))
                    {
                        progress = PROGRESS_FINISHING;
                        sendSignal(SIGNAL_FINISH);
                        sendResult((i == TEAM_BAMBOO) ? RESULT_MUSH_WIN : RESULT_BAMBOO_WIN);

                        for (int i = 0; i < TEAM_NUMBER; i++)
                        {
                            DataBlock data;
                            data.setCommand2DataBlock(NC_SEND_TEAM_STATUS);
                            data.setData(&i, sizeof(TEAM_ID));
                            data.setData(&tStatus[i], sizeof(TeamStatus));
                            NetworkManager::sendData(ALL_CLIENTS, data, data.getDataSize());
                        }

                        timer = 2000;
                        break;
                    }
                }

                pObject->killObject();
                ItemSpawner::currentItemNum--;

                //effect
                //当たり判定処理
                sendEffect(EFFECT_BOMB, pObject->transform.position);
            }
            else if (OBJECT_JEWEL_R <= pObject->objectId && pObject->objectId <= OBJECT_JEWEL_B)
            {
                for (int i = 0; i < TEAM_NUMBER; i++)
                {
                    if (Collider::isCollision(pObject->collider, staticObjectStatus[SOBJECT_TOWER_R + i].collider))
                    {
                        sendEffect(EFFECT_UP, pObject->transform.position);
                        pObject->killObject();
                        setBuff((TEAM_ID)i, (BUFF_ID)(pObject->objectId - OBJECT_JEWEL_R));

                        break;
                    }
                }
            }
        }
    }
    for (int i = 0; i < MAX_PLAYERS; i++)
    {
        //spawning
        charaSpawningProcess(i);

        //moving
        charaMovingProcess(i);

        //grabbing
        if (cStatus[i].hp > 0)
        {
            charaGrabbingProcess(i);
        }
    }
    for (int i = 0; i < TEAM_NUMBER; i++)
    {
        buffProcess(i);
    }

    return nextScene;
}

void SceneMainGame::sendData()
{
    if (progress == PROGRESS_FINISHING)
    {
        return;
    }
    if (gameInitable)
    {
        DataBlock data;
        data.setCommand2DataBlock(NC_MOVE_SCENE);
        NetworkManager::sendData(ALL_CLIENTS, data, data.getDataSize());
        gameInitable = false;

        sendSignal(SIGNAL_READY);
    }
    for (int i = 0; i < TEAM_NUMBER; i++)
    {
        DataBlock data;
        data.setCommand2DataBlock(NC_SEND_TEAM_STATUS);
        data.setData(&i, sizeof(TEAM_ID));
        data.setData(&tStatus[i], sizeof(TeamStatus));
        NetworkManager::sendData(ALL_CLIENTS, data, data.getDataSize());
    }
    for (int i = 0; i < MAX_PLAYERS; i++)
    {
        DataBlock data;
        data.setCommand2DataBlock(NC_SEND_CHARA_DATA);
        data.setData(&i, sizeof(int));
        CCharaData charaData = cStatus[i].getDataForClient();
        data.setData(&charaData, sizeof(CCharaData));
        NetworkManager::sendData(ALL_CLIENTS, data, data.getDataSize());
    }
    for (int i = 0; i < SOBJECT_NUMBER; i++)
    {
        OBJECT_TYPE type = OBJECT_TYPE_STATIC;
        CObjectData objectData = staticObjectStatus[i].getDataForClient();

        DataBlock data;
        data.setCommand2DataBlock(NC_SEND_OBJECT_DATA);
        data.setData(&i, sizeof(int));
        data.setData(&type, sizeof(OBJECT_TYPE));
        data.setData(&objectData, sizeof(CObjectData));
        NetworkManager::sendData(ALL_CLIENTS, data, data.getDataSize());
    }
    for (int i = 0; i < MAX_DYNAMIC_OBJECTS; i++)
    {
        GameObjectStatus *pObject = &dynamicObjectStatus[i];
        if (!pObject->isUpdated)
        {
            continue;
        }
        OBJECT_TYPE type = OBJECT_TYPE_DYNAMIC;
        CObjectData objectData = dynamicObjectStatus[i].getDataForClient();

        DataBlock data;
        data.setCommand2DataBlock(NC_SEND_OBJECT_DATA);
        data.setData(&i, sizeof(int));
        data.setData(&type, sizeof(OBJECT_TYPE));
        data.setData(&objectData, sizeof(CObjectData));
        NetworkManager::sendData(ALL_CLIENTS, data, data.getDataSize());
        dynamicObjectStatus[i].isUpdated = false;
    }
}
void SceneMainGame::sendSignal(SIGNAL_ID signal)
{
    DataBlock data;
    data.setCommand2DataBlock(NC_SEND_SIGNAL);
    data.setData(&signal, sizeof(SIGNAL_ID));
    NetworkManager::sendData(ALL_CLIENTS, data, data.getDataSize());
}
void SceneMainGame::sendResult(RESULT_ID resultData)
{
    DataBlock data;
    data.setCommand2DataBlock(NC_SEND_RESULT_DATA);
    data.setData(&resultData, sizeof(RESULT_ID));
    NetworkManager::sendData(ALL_CLIENTS, data, data.getDataSize());
}
void SceneMainGame::sendEffect(EFFECT_ID effect, Vector3f pos)
{
    DataBlock data;
    data.setCommand2DataBlock(NC_SEND_EFFECT_DATA);
    data.setData(&effect, sizeof(EFFECT_ID));
    data.setData(&pos, sizeof(Vector3f));
    NetworkManager::sendData(ALL_CLIENTS, data, data.getDataSize());
}
void SceneMainGame::charaSpawningProcess(int id)
{
    CharaStatus *pChara = &cStatus[id];
    if (pChara->spawningTime <= 0)
    {
        return;
    }
    pChara->spawningTime--;
    if (pChara->spawningTime == 0)
    {
        pChara->setPos((pChara->teamId == TEAM_MUSH) ? Vector3f(-20.0f, 0.0f, 0.0f) : Vector3f(20.0f, 0.0f, 0.0f));
        pChara->hp = MAX_CHARA_HP;
    }
}
void SceneMainGame::charaMovingProcess(int id)
{
    Vector2f controllerVec = clientsData[id].controllerParam.axisL;

    if (clientsData[id].controllerParam.buttonDown[CT_DECITION_OR_ATTACK] && !clientsData[id].controllerParam.buttonState[CT_DECITION_OR_ATTACK] && !cStatus[id].atkMode)
    {
        cStatus[id].atkMode = true;
    }
    if (cStatus[id].atkMode)
    {
        cStatus[id].atkMode = cStatus[id].attack();
    }
    cStatus[id].move(Vector3f(controllerVec.x, 0.0f, controllerVec.y));
}
void SceneMainGame::charaGrabbingProcess(int id)
{
    ControllerParam *controller = &clientsData[id].controllerParam;
    if (controller->buttonDown[CT_GRUB] && !controller->buttonState[CT_GRUB])
    {
        cStatus[id].weaponEvent(&dynamicObjectStatus[0]);
    }
}
void SceneMainGame::objectMovingProcess(int id)
{
    GameObjectStatus *pObject = &dynamicObjectStatus[id];
    *pObject = ObjectController(&staticObjectStatus[0]).moveObject(*pObject);
}

bool SceneMainGame::towerDamageProcess(int id, Collider collider, unsigned int damageValue)
{
    if (Collider::isCollision(staticObjectStatus[SOBJECT_TOWER_R + id].collider, collider))
    {
        if (tStatus[id].hp <= damageValue)
        {
            tStatus[id].hp = 0;
            return true;
        }
        else
        {
            tStatus[id].hp -= damageValue;
        }
    }
    return false;
}
void SceneMainGame::buffProcess(int id)
{
    for (int i = 0; i < BUFF_NUMBER; i++)
    {
        unsigned int *pTimer = &tStatus[id].buffTimer[i];
        bool *pBuff = &tStatus[id].buff[i];
        if (!(*pBuff))
        {
            continue;
        }

        tStatus[id].buffTimer[i]--;

        if (*pTimer == 0)
        {
            resetBuff((TEAM_ID)id, (BUFF_ID)i);
        }
    }
}

void SceneMainGame::setBuff(TEAM_ID teamId, BUFF_ID buffId)
{
    unsigned int time;
    if (buffId == BUFF_ATK)
    {
        time = 4000;
        if (!tStatus[teamId].buff[buffId])
        {
            for (int i = 0; i < MAX_PLAYERS; i++)
            {
                if (teamId == cStatus[i].teamId)
                {
                    cStatus[i].damageValue *= 2;
                }
            }
        }
    }
    else if (buffId == BUFF_HP)
    {
        time = 500;
        for (int i = 0; i < MAX_PLAYERS; i++)
        {
            if (teamId == cStatus[i].teamId)
            {
                cStatus[i].hp = MAX_CHARA_HP;
            }
        }
    }
    else if (buffId == BUFF_SPEED)
    {
        time = 3000;
        if (!tStatus[teamId].buff[buffId])
        {
            for (int i = 0; i < MAX_PLAYERS; i++)
            {
                if (teamId == cStatus[i].teamId)
                {
                    cStatus[i].speedValue *= 2;
                }
            }
        }
    }
    tStatus[teamId].buff[buffId] = true;
    tStatus[teamId].buffTimer[buffId] = time;
}
void SceneMainGame::resetBuff(TEAM_ID teamId, BUFF_ID buffId)
{
    if (buffId == BUFF_ATK)
    {
        for (int i = 0; i < MAX_PLAYERS; i++)
        {
            if (teamId == cStatus[i].teamId)
            {
                cStatus[i].damageValue /= 2;
            }
        }
    }
    else if (buffId == BUFF_SPEED)
    {
        for (int i = 0; i < MAX_PLAYERS; i++)
        {
            if (teamId == cStatus[i].teamId)
            {
                cStatus[i].speedValue /= 2;
            }
        }
    }
    tStatus[teamId].buff[buffId] = false;
}