#include "./sceneLoading.h"
#include "../../common/network/networkCommand.h"
#include "../../common/network/dataBlock/dataBlock.h"
#include "../network/networkManager.h"
#include "../../common/controllerParam/controllerParam.h"
#include <stdio.h>
bool SceneLoading::init()
{
    for(int i = 0; i < MAX_CLIENTS; i++)
    {
        exit[i] = false;
    }
    return true;
}
SCENE_ID SceneLoading::executeCommand(int command, int pos)
{
    if (command == NC_SEND_NAME)
    {
        NetworkManager::recvData(pos, &gameData[pos].name, sizeof(char *));
        exit[pos] = true;
    }
    int count = 0;
    for (int i = 0; i < MAX_CLIENTS; i++)
    {
        if (exit[i])
        {
            count++;
        }
    }

    if (count == MAX_CLIENTS)
    {
        DataBlock data;

        data.setCommand2DataBlock(NC_MOVE_SCENE);
        NetworkManager::sendData(ALL_CLIENTS, data, data.getDataSize());
        return SI_CHARASELECT;
    }
    return SI_LOADING;
}
