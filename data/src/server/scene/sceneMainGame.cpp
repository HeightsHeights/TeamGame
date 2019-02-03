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
    upDate();
    sendData();
    return nextScene;
}

void SceneMainGame::upDate()
{
    if (gameInitable)
    {
        for (int i = 0; i < MAX_PLAYERS; i++)
        {
            Transform charaTransform = Transform(Vector3f(20.0f, 0.0f, 0), Vector3f_ZERO, Vector3f(1.0f, 3.0f, 1.0f));
            cStatus[i] = CharaStatus(clientsData[i].teamId, &charaTransform);

            Vector3f tmpPos(-20.0f, 20.0f, 0.0f);
            // Transform tmpTransform = Transform(tmpPos, Vector3f_ZERO, Vector3f(1.5f, 1.5f, 1.5f));
            // Collider tmpCollider(Sphere(tmpPos, 3));
            // dynamicObjectStatus[0] = GameObjectStatus(OBJECT_BOMB, &tmpTransform, &tmpCollider);
            Transform tmpTransform = Transform(tmpPos, Vector3f_ZERO, Vector3f(5.0f, 5.0f, 5.0f));
            Collider tmpCollider(Sphere(tmpPos, 4));
            dynamicObjectStatus[0] = GameObjectStatus(OBJECT_JEWEL_B, &tmpTransform, &tmpCollider);
        }
    }
    for (int i = 0; i < MAX_DYNAMIC_OBJECTS; i++)
    {
        //moving
        if (!dynamicObjectStatus[i].exist)
        {
            continue;
        }
        objectMovingProcess(i);
    }
    for (int i = 0; i < MAX_PLAYERS; i++)
    {
        //spawning
        charaSpawningProcess(i);

        //moving
        charaMovingProcess(i);

        //grabbing
        charaGrabbingProcess(i);
        // if (clientsData[i].controllerParam.buttonDown[CT_DECITION_OR_ATTACK] && !clientsData[i].controllerParam.buttonState[CT_DECITION_OR_ATTACK] && !cStatus[i].atkMode)
        // {
        //     cStatus[i].atkMode = true;
        // }
        // if (!cStatus[i].atkMode)
        // {
        //     cStatus[i].atkMode = cStatus[i].attack();
        // }
        // if (clientsData[i].controllerParam.buttonDown[CT_GRUB] && !clientsData[i].controllerParam.buttonState[CT_GRUB] || cStatus[i].haveWeapon == true)
        // {
        //     cStatus[i].weaponThrow(cStatus[i].haveWeapon);
        // }
    }
}

void SceneMainGame::sendData()
{
    if (gameInitable)
    {
        DataBlock data;
        data.setCommand2DataBlock(NC_MOVE_SCENE);
        NetworkManager::sendData(ALL_CLIENTS, data, data.getDataSize());
        gameInitable = false;
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
        data.setCommand2DataBlock(NC_SEND_RESULT_DATA);
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
        if (!dynamicObjectStatus[i].isUpdated)
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