#include "./sceneChara.h"
#include "../../common/network/networkCommand.h"
#include "../../common/network/dataBlock/dataBlock.h"
#include "../network/networkManager.h"
#include <stdio.h>
bool SceneChara::init()
{
    return true;
}
SCENE_ID SceneChara::executeCommand(int command, int pos)
{
    if (command == NC_READY && ready[pos] == false)
    {
        num = pos;
        ready[pos] = true;
        DataBlock data;
        data.setCommand2DataBlock(NC_SERVER_2_CLIENT);
        data.setData(&num, sizeof(int));
        NetworkManager::sendData(ALL_CLIENTS, data, data.getDataSize());
    }
    // else if (command == NC_MAINGAME)
    // {
    //     DataBlock data;
    //     data.setCommand2DataBlock(NC_SERVER_MAINGAME);
    //     NetworkManager::sendData(ALL_CLIENTS, data, data.getDataSize());
    //     return SI_MAIN;
    // }
    return SI_CHARASELECT;
}