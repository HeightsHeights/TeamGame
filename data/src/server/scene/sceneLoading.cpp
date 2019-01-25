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
<<<<<<< HEAD
    if (command == NC_START)
    {
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
=======
    // if (command == NC_START)
    // {
    //     NetworkManager::recvData(pos, &gameData[pos].name, sizeof(char *));
    //     exit[pos] = true;
    // }
    // int count = 0;
    // for (int i = 0; i < MAX_CLIENTS; i++)
    // {
    //     if (exit)
    //     {
    //         count++;
    //     }
    // }
>>>>>>> 221e370b01f7ab71cd9a8ba40827cb70d3e27222

    // if (count == MAX_CLIENTS)
    // {
    //     DataBlock data;

<<<<<<< HEAD
        data.setCommand2DataBlock(NC_SERVER_CHARASELSECT);
        NetworkManager::sendData(ALL_CLIENTS, data, data.getDataSize());
        return SI_CHARASELECT;
    }
=======
    //     data.setCommand2DataBlock(NC_SERVER_CHARASELSECT);
    //     NetworkManager::sendData(ALL_CLIENTS, data, data.getDataSize());
    // }
>>>>>>> 221e370b01f7ab71cd9a8ba40827cb70d3e27222
    return SI_LOADING;
}
