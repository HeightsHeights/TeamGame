#include "./sceneMainGame.h"

#include "../network/networkManager.h"
#include "../../common/network/dataBlock/dataBlock.h"
#include "../../common/controllerParam/controllerParam.h"

bool SceneMainGame::init()
{
    Obb collider[] = {
        Obb(Vector3f(0, 0, 0), Touple3f(180, 0, 100)),     //床
        Obb(Vector3f(-100, 10, 40), Touple3f(10, 10, 10)), //壁
        Obb(Vector3f(-65, 10, -40), Touple3f(10, 10, 10)), //壁
        Obb(Vector3f(0, 10, 0), Touple3f(10, 10, 10)),     //壁
        Obb(Vector3f(85, 10, -40), Touple3f(10, 10, 10)),  //壁
        Obb(Vector3f(50, 10, 40), Touple3f(10, 10, 10)),   //壁
        Obb(Vector3f(-140, 20, 0), Touple3f(3, 20, 3)),    //塔
        Obb(Vector3f(-140, 20, 0), Touple3f(3, 20, 3)),    //塔
    };

    // for (int i = 0; i < MAX_PLAYERS; i++)
    // {
    //     staticCollider[i].center = collider[i].center;
    //     for (int j = 0; j < 3; j++)
    //     {
    //         staticCollider[i].length[j] = collider[i].length[j];
    //     }
    // }

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
    for (int i = 0; i < MAX_PLAYERS; i++)
    {
        // bool isCollision = false;
        // TEAM_ID id = clientsData[i].teamId;
        // chara[i].speed = tStatus[id].buff[BUFF_SPEED] ? 2.0f : 2.0f;

        // Vector2f axisL = clientsData[i].controllerParam.axisL;

        // CharaCollider[i].center += Vector3f(axisL.x, 0.0f, axisL.y);
        // for (int j = 1; j < MAX_STATIC_OBJECTS; j++)
        // {
        //     if (CharaCollider[i].isCollision(staticCollider[j]))
        //     {
        //         isCollision = true;
        //     }
        // }
        // if (!isCollision)
        // {
        //     chara[i].move(Vector3f(axisL.x, 0.0f, axisL.y));
        //     cStatus[i].transform = chara[i].transform;
        // }
        // else
        // {
        //     CharaCollider[i].center -= Vector3f(axisL.x, 0.0f, axisL.y);
        // }
    }
}

void SceneMainGame::sendData()
{
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
    for (int i = 0; i < MAX_DYNAMIC_OBJECTS; i++)
    {
        DataBlock data;
        data.setCommand2DataBlock(NC_SEND_OBJECT_DATA);
        data.setData(&i, sizeof(int));
        CObjectData objectData = dynamicObjectStatus[i].getDataForClient();
        data.setData(&objectData, sizeof(CObjectData));
        NetworkManager::sendData(ALL_CLIENTS, data, data.getDataSize());
    }
}