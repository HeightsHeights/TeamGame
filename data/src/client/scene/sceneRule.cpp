#include "./sceneRule.h"
#include "../../common/network/networkCommand.h"
#include "../../common/network/dataBlock/dataBlock.h"
#include "../network/networkManager.h"
#include "../../common/scene/sceneParam.h"
SceneRule::SceneRule(WindowManager *window) : BaseScene(window)
{
}
bool SceneRule::init()
{
    //position = Vector3f_ZERO;
    return true;
}
SCENE_ID SceneRule::reactController(ControllerParam param)
{
    // DataBlock data;
    // data.setCommand2DataBlock(NC_CONTROLLER_INFO);
    // data.setData(&param, sizeof(ControllerParam));
    // NetworkManager::sendData(data, data.getDataSize());
    return SI_RULE;
}
SCENE_ID SceneRule::executeCommand(int command)
{
    // if (command == NC_SERVER_MASTER_CLIENT)
    // {
    //     SceneParam paramNet;
    //     NetworkManager::recvData(&paramNet,sizeof(SceneParam));
    //     position.x = paramNet.axis.x;
    //     position.y = paramNet.axis.y;    
    // }
    return SI_RULE;
}
void SceneRule::draw3D()
{
}
void SceneRule::draw2D()
{
}