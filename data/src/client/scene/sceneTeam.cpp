#include "./sceneTeam.h"
#include "../render/shader/shaderManager.h"
#include "../../common/network/networkCommand.h"
#include "../../common/network/dataBlock/dataBlock.h"

SceneTeam::SceneTeam(WindowManager *window) : BaseScene(window)
{
}
bool SceneTeam::init()
{
    // for(int i = 0;i < 2; i++){
    //     position[i] = Vector2f_ZERO;
    // }
    return true;
}
SCENE_ID SceneTeam::reactController(ControllerParam param)
{
    // DataBlock data;
    // data.setCommand2DataBlock(NC_CONTROLLER_INFO);
    // data.setData(&param, sizeof(ControllerParam));
    // NetworkManager::sendData(data, data.getDataSize());
    return SI_TEAM;
}
SCENE_ID SceneTeam::executeCommand(int command)
{
    // if (command == NC_SERVER_2_CLIENT)
    // {
    //     Vector2f positionData[2];
    //     for(int i = 0;i < 2; i++){
    //     NetworkManager::recvData(positionData[i],sizeof(Vector2f));
    //     position[i].x = positionData[i].x;
    //     }
    // }
    return SI_TEAM;
}
void SceneTeam::draw3D()
{
}
void SceneTeam::draw2D()
{
}