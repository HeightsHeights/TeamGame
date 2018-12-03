#include "./sceneTitle.h"
#include "../../common/network/networkCommand.h"
#include "../../common/network/dataBlock/dataBlock.h"
#include "../network/networkManager.h"
#include "../../common/controllerParam/controllerParam.h"
#include <stdio.h>
bool SceneTitle::init()
{
    for (int i = 0; i < 2; i++)
    {
        position[i] = Vector3f_ZERO;
    }
    return true;
}
SCENE_ID SceneTitle::executeCommand(int command, int pos)
{

    if (command == NC_CONTROLLER_INFO)
    {
        ControllerParam paramData;
        NetworkManager::recvData(pos, &paramData, sizeof(ControllerParam));
        position[pos].x = paramData.axisL.x;
        position[pos].z = paramData.axisL.y;

        DataBlock data;
        NETWORK_COMMAND command = NC_SERVER_2_CLIENT;
        data.setData(&command, sizeof(NETWORK_COMMAND));
        data.setData(position[0], sizeof(Vector3f));
        data.setData(position[1], sizeof(Vector3f));
        NetworkManager::sendData(ALL_CLIENTS, data, data.getDataSize());
    }
    return SI_TITLE;
}
