#include "./sceneChara.h"
#include "../../common/network/networkCommand.h"
#include "../../common/network/dataBlock/dataBlock.h"
#include "../network/networkManager.h"
#include "../../common/scene/sceneParam.h"
SceneChara::SceneChara(WindowManager *window) : BaseScene(window)
{
}
bool SceneChara::init()
{
    //position = Vector3f_ZERO;
    return true;
}
SCENE_ID SceneChara::reactController(ControllerParam param)
{
    // DataBlock data;
    // data.setCommand2DataBlock(NC_CONTROLLER_INFO);
    // data.setData(&param, sizeof(ControllerParam));
    // NetworkManager::sendData(data, data.getDataSize());
    return SI_CHARA;
}
SCENE_ID SceneChara::executeCommand(int command)
{
    // if (command == NC_SERVER_2_CLIENT)
    // {
    //     SceneParam paramNet;
    //     NetworkManager::recvData(&paramNet,sizeof(SceneParam));
    //     position.x = paramNet.axis.x;
    //     position.y = paramNet.axis.y;    
    // }
    return SI_CHARA;
}
void SceneChara::draw3D()
{
}
void SceneChara::draw2D()
{
}