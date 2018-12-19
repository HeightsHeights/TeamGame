#include "./sceneChara.h"
#include "../../common/network/networkCommand.h"
#include "../../common/network/dataBlock/dataBlock.h"
#include "../network/networkManager.h"
#include "../../common/controllerParam/controllerParam.h"
#include <stdio.h>
bool SceneChara::init()
{
    for (int i = 0; i < 2; i++)
    {
        param[i].axis = Vector3f_ZERO;
    }
    return true;
}
SCENE_ID SceneChara::executeCommand(int command, int pos)
{
    if (command == NC_CONTROLLER_INFO)
    {
        ControllerParam paramData;
        NetworkManager::recvData(pos, &paramData, sizeof(ControllerParam));
        param[pos].axis.x = paramData.axisL.x;
        param[pos].axis.z = paramData.axisL.y;
        if(paramData.buttonDown[CT_DECITION_OR_ATTACK])
            param[pos].button = true;
        else 
            param[pos].button = false;

        DataBlock data;

        data.setCommand2DataBlock(NC_SERVER_2_CLIENT);

        data.setData(&param[0], sizeof(SceneParam));
        data.setData(&param[1], sizeof(SceneParam));
        NetworkManager::sendData(ALL_CLIENTS, data, data.getDataSize());
    }
    return SI_CHARA;
}