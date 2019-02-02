#include "./sceneChara.h"
#include "../../common/network/networkCommand.h"
#include "../../common/network/dataBlock/dataBlock.h"
#include "../../common/controllerParam/controllerParam.h"
#include <stdio.h>

Player SceneChara::pl[MAX_PLAYERS];

bool SceneChara::init()
{
    for (int i = 0; i < MAX_PLAYERS; i++)
    {
        button[i] = false;
    }
    return true;
}
SCENE_ID SceneChara::executeCommand(int command, int pos)
{
    if (command == NC_MOVE_SCENE)
    {
        for (int i = 0; i < MAX_PLAYERS; i++)
        {
            clientsData[i].teamId = (pl[i].position.x == 0) ? TEAM_MUSH : TEAM_BAMBOO;
        }

        DataBlock data;
        data.setCommand2DataBlock(NC_MOVE_SCENE);
        NetworkManager::sendData(ALL_CLIENTS, data, data.getDataSize());
        return SI_MAIN;
    }
    else if (command == NC_FINISH)
    {
        DataBlock data;
        data.setCommand2DataBlock(NC_FINISH);
        NetworkManager::sendData(ALL_CLIENTS, data, data.getDataSize());
        return SI_NUMBER;
    }

    if (command == NC_SEND_CONTROLLER_PARAM)
    {
        ControllerParam paramData;
        NetworkManager::recvData(pos, &paramData, sizeof(ControllerParam));

        if (button[pos] == true)
        {
            pl[pos].position.x += paramData.axisL.x;
            button[pos] = false;
        }

        if (paramData.axisL.x == 0)
        {
            button[pos] = true;
        }

        if (pl[pos].position.x > 1)
        {
            pl[pos].position.x = 0;
        }
        else if (pl[pos].position.x < 0)
        {
            pl[pos].position.x = 1;
        }

        DataBlock data;

        data.setCommand2DataBlock(NC_SEND_CONTROLLER_PARAM);
        data.setData(&pos, sizeof(int));
        data.setData(pl[pos].position, sizeof(Vector2f));
        NetworkManager::sendData(ALL_CLIENTS, data, data.getDataSize());
    }
    return SI_CHARASELECT;
}
SCENE_ID SceneChara::dataProcessing()
{
    return SI_CHARASELECT;
}