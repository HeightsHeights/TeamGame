#include "./sceneRule.h"
#include "../../common/network/networkCommand.h"
#include "../../common/network/dataBlock/dataBlock.h"
#include "../network/networkManager.h"
#include "../../common/controllerParam/controllerParam.h"
#include <stdio.h>

bool SceneRule::init()
{
    for (int i = 0; i < 2; i++)
    {
        position = Vector2f_ZERO;
    }
    return true;
}
SCENE_ID SceneRule::executeCommand(int command, int pos)
{
    if (pos == 0)
    {
        if (command == NC_CONTROLLER_INFO)
        {
            ControllerParam paramData;
            NetworkManager::recvData(pos, &paramData, sizeof(ControllerParam));
            position.x = paramData.axisL.x;
            position.y = paramData.axisL.y;
            DataBlock data;
            data.setCommand2DataBlock(NC_SERVER_2_CLIENT);
            data.setData(position, sizeof(Vector2f));

            NetworkManager::sendData(ALL_CLIENTS, data, data.getDataSize());
        }
    }
    return SI_RULE;
}