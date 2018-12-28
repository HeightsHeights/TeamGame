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
        int count = 0;
        int gClientNum = NetworkManager::getGClientNum();
        ready[pos] = true;

        for(int i = 0; i < gClientNum; i++){
            if(ready[i] == true){
                count++;
            }
        }

        if(count == gClientNum){
            DataBlock data;
            data.setCommand2DataBlock(NC_SERVER_MAINGAME);
            NetworkManager::sendData(ALL_CLIENTS, data, data.getDataSize());
            return SI_MAIN;
        }
        else{
            DataBlock data;
            data.setCommand2DataBlock(NC_SERVER_2_CLIENT);
            data.setData(&pos, sizeof(int));
            NetworkManager::sendData(ALL_CLIENTS, data, data.getDataSize());
        }
    }
    return SI_CHARASELECT;
}