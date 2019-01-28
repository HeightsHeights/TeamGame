#include "./sceneMainGame.h"

#include "../network/networkManager.h"
#include "../../common/network/dataBlock/dataBlock.h"
#include "../../common/controllerParam/controllerParam.h"

#include "../../common/gameData/gameData.h"

bool SceneMainGame::init()
{
    Vector3f collider[] = {
        Obb(), //床
        Obb(), //壁
        Obb(), //壁
        Obb(), //壁
        Obb(), //壁
        Obb(), //壁
        Obb(), //塔
        Obb(), //塔
    };

    for (int i = 0; i < TEAM_NUMBER; i++)
    {
        tStatus[i] = TeamStatus();
    }

    for (int i = 0; i < MAX_STATIC_OBJECTS; i++)
    {
    }

    return true;
}
SCENE_ID SceneMainGame::executeCommand(int command, int pos)
{
    SCENE_ID nextScene = SI_MAIN;

    if (command == NC_SEND_CONTROLLER_PARAM)
    {
        ControllerParam paramData;
        NetworkManager::recvData(pos, &paramData, sizeof(ControllerParam));

        if (paramData.buttonDown[CT_FINISH])
        {
            DataBlock data;
            data.setCommand2DataBlock(NC_FINISH);
            NetworkManager::sendData(ALL_CLIENTS, data, data.getDataSize());
            nextScene = SI_NUMBER;
        }
        else
        {
            clientsData[pos].controllerParam = paramData;
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
    for (int i = 0; i < MAX_CLIENTS; i++)

    {
        bool isCollision = false;
        TEAM_ID id = clientsData[i].teamId;
        chara[i].speed = tStatus[id].buff[BUFF_SPEED] ? 2.0f : 2.0f;

        Vector2f axisL = clientsData[i].controllerParam.axisL;

        CharaCollider[i].center += Vector3f(axisL.x, 0.0f, axisL.y);
        for (int j = 1; j < MAX_STATIC_OBJECTS; j++)
        {
            if (CharaCollider[i].isCollision(staticCollider[j]))
            {
                isCollision = true;
            }
        }
        if (!isCollision)
        {
            chara[i].move(Vector3f(axisL.x, 0.0f, axisL.y));
        }
        else
        {
            CharaCollider[i].center -= Vector3f(axisL.x, 0.0f, axisL.y);
        }
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

    for (int i = 0; i < MAX_CLIENTS; i++)
    {
        DataBlock data;
        data.setCommand2DataBlock(NC_SEND_OBJECT_DATA);
        data.setData(&i, sizeof(int));
        data.setData(&chara, sizeof(Chara));
        NetworkManager::sendData(ALL_CLIENTS, data, data.getDataSize());
    }
}