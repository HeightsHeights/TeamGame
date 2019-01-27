#include "./sceneMainGame.h"

#include "../network/networkManager.h"
#include "../../common/network/dataBlock/dataBlock.h"
#include "../../common/controllerParam/controllerParam.h"

bool SceneMainGame::init()
{
    return true;
}
SCENE_ID SceneMainGame::executeCommand(int command, int pos)
{
    SCENE_ID nextScene = SI_MAIN;

    if (command == NC_SEND_CONTROLLER_PARAM)
    {
        ControllerParam paramData;
        NetworkManager::recvData(pos, &paramData, sizeof(ControllerParam));

        if (paramData.buttonDown[CT_FINISH])
        {
            DataBlock data;
            data.setCommand2DataBlock(NC_FINISH);
            NetworkManager::sendData(ALL_CLIENTS, data, data.getDataSize());
            nextScene = SI_NUMBER;
        }
    }
    return nextScene;
}
SCENE_ID SceneMainGame::dataProcessing()
{
    return SI_MAIN;
}