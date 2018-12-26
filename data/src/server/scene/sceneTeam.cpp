#include "./sceneTeam.h"
#include "../../common/network/networkCommand.h"
#include "../../common/network/dataBlock/dataBlock.h"
#include "../network/networkManager.h"
#include "../../common/controllerParam/controllerParam.h"
#include <stdio.h>

bool SceneTeam::init()
{
    for (int i = 0; i < 2; i++)
    {
        position[i] = Vector2f_ZERO;
    }
    return true;
}
SCENE_ID SceneTeam::executeCommand(int command, int pos)
{
    if (command == NC_CONTROLLER_INFO)
    {
        ControllerParam paramData;
        NetworkManager::recvData(pos, &paramData, sizeof(ControllerParam));

        if(button[pos] == true){
            position[pos].x = paramData.axisL.x;
            button[pos] = false;
        }
        else{
            position[pos].x = 0;
        } 

        if(paramData.axisL.x == 0){
            button[pos] = true;
        }
        

        DataBlock data;

        data.setCommand2DataBlock(NC_SERVER_2_CLIENT);

        data.setData(position[0], sizeof(Vector2f));
        data.setData(position[1], sizeof(Vector2f));
        NetworkManager::sendData(ALL_CLIENTS, data, data.getDataSize());
    }
    else if(command == NC_READY){
        DataBlock data;
        data.setCommand2DataBlock(NC_SERVER_CHARASELSECT);
        NetworkManager::sendData(ALL_CLIENTS, data, data.getDataSize());
        return SI_CHARASELECT;
    }
    return SI_TEAMSELECT;
}