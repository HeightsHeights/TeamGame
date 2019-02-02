#include "./sceneLoading.h"
#include "../../common/network/dataBlock/dataBlock.h"
#include "../network/networkManager.h"
#include "../../common/controllerParam/controllerParam.h"
#include <stdio.h>
bool SceneLoading::init()
{
    numRecieveName = 0;
    return true;
}
SCENE_ID SceneLoading::executeCommand(int command, int pos)
{
    SCENE_ID nextScene = SI_LOADING;
    if (command == NC_SEND_NAME)
    {
        NetworkManager::recvData(pos, clientsData[pos].name, sizeof(char *));
        numRecieveName++;
    }

    if (numRecieveName == MAX_PLAYERS)
    {
        for (int i = 0; i < MAX_PLAYERS; i++)
        {
            DataBlock data;
            data.setCommand2DataBlock(NC_SEND_ID);
            data.setData(&i, sizeof(int));
            NetworkManager::sendData(i, &data, data.getDataSize());
        }

        for (int i = 0; i < MAX_PLAYERS; i++)
        {
            DataBlock data;
            data.setCommand2DataBlock(NC_SEND_NAME);
            data.setData(&i, sizeof(int));
            data.setData(&clientsData[i].name, sizeof(char *));
            NetworkManager::sendData(ALL_CLIENTS, &data, data.getDataSize());
        }

        DataBlock data;
        data.setCommand2DataBlock(NC_MOVE_SCENE);
        NetworkManager::sendData(ALL_CLIENTS, data, data.getDataSize());
        nextScene = SI_CHARASELECT;
    }
    return nextScene;
}

SCENE_ID SceneLoading::dataProcessing()
{
    return SI_LOADING;
}