#include "./sceneRule.h"
#include "../../common/network/networkCommand.h"
#include "../../common/network/dataBlock/dataBlock.h"
#include "../network/networkManager.h"
#include "../../common/controllerParam/controllerParam.h"
#include <stdio.h>

bool SceneRule::init()
{
    param.axis = Vector3f_ZERO;
    
    return true;
}
SCENE_ID SceneRule::executeCommand(int command, int pos)
{
    if(pos == 0){
        if (command == NC_CONTROLLER_INFO)
        {
            ControllerParam paramData;
            NetworkManager::recvData(pos, &paramData, sizeof(ControllerParam));
            param.axis.x = paramData.axisL.x;
            param.axis.y = paramData.axisL.y;
            if(paramData.buttonDown[CT_DECITION_OR_ATTACK])
                param.button = true;
            else 
                param.button = false;
            DataBlock data;

            data.setCommand2DataBlock(NC_SERVER_MASTER_CLIENT);
            data.setData(&param, sizeof(SceneParam));
            NetworkManager::sendData(pos, data, data.getDataSize());
        }
    }
    return SI_RULE;
}