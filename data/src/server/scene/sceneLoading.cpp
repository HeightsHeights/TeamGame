#include "./sceneLoading.h"
#include "../../common/network/dataBlock/dataBlock.h"
#include "../network/networkManager.h"
#include "../../common/controllerParam/controllerParam.h"
#include <stdio.h>
bool SceneLoading::init()
{
    for (int i = 0; i < MAX_PLAYERS; i++)
    {
        exist[i] = false;
    }
    return true;
}
SCENE_ID SceneLoading::executeCommand(int command, int pos)
{
    if (command == NC_SEND_NAME)
    {
        NetworkManager::recvData(pos, clientsData[pos].name, sizeof(char *));
        exist[pos] = true;
    }
    int count = 0;
    for (int i = 0; i < MAX_PLAYERS; i++)
    {
        if (exist[i])
        {
            count++;
        }
    }

    if (count == MAX_PLAYERS)
    {
        for (int i = 0; i < MAX_PLAYERS; i++)
        {
            DataBlock data;
            data.setCommand2DataBlock(NS_SEND_ID);
            data.setData(&i, sizeof(int));
            NetworkManager::sendData(pos, &data, data.getDataSize());
        }
        DataBlock data;
        data.setCommand2DataBlock(NC_MOVE_SCENE);
        NetworkManager::sendData(ALL_CLIENTS, data, data.getDataSize());
        return SI_CHARASELECT;
    }
    return SI_LOADING;
}

SCENE_ID SceneLoading::dataProcessing()
{
    return SI_LOADING;
}