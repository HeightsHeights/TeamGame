#include "./sceneMainGame.h"

#include "../network/networkManager.h"
#include "../../common/network/dataBlock/dataBlock.h"
#include "../../common/controllerParam/controllerParam.h"

bool SceneMainGame::init()
{
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

    return SI_MAIN;
}

void SceneMainGame::upDate()
{
    for (int i = 0; i < MAX_CLIENTS; i++)
    {
        TEAM_ID id = clientsData[i].teamId;
        chara[i].speed = tStatus[id].buff[BUFF_SPEED] ? 2.0f : 2.0f;

        Vector2f axisL = clientsData[i].controllerParam.axisL;
        chara[i].move(Vector3f(axisL.x, 0.0f, axisL.y));
    }
}
void SceneMainGame::sendData()
{
}