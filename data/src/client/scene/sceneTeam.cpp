#include "./sceneTeam.h"
#include "../render/shader/shaderManager.h"
#include "../../common/network/networkCommand.h"
#include "../../common/network/dataBlock/dataBlock.h"
#include "../network/networkManager.h"

SceneTeam::SceneTeam(WindowManager *window) : BaseScene(window)
{
}
SceneTeam::SceneTeam(WindowManager *window, ConfigData *config) : BaseScene(window, config)
{
}
bool SceneTeam::init()
{
    // for(int i = 0;i < 2; i++){
    //     position[i] = Vector2f_ZERO;
    // }
    return true;
}
//static int count;
SCENE_ID SceneTeam::reactController(ControllerParam param)
{
    // count = 0;
    // for(int i = 0;i < 2; i++){
    //   if(position[i].x == 1)
    //     count++;
    // }
    // if(count == 1){
    //     DataBlock data;
    //     data.setCommand2DataBlock(NC_READY);
    //     data.setData(&param, sizeof(ControllerParam));
    //     NetworkManager::sendData(data, data.getDataSize());
    // }
    // else{
    //     DataBlock data;
    //     data.setCommand2DataBlock(NC_CONTROLLER_INFO);
    //     data.setData(&param, sizeof(ControllerParam));
    //     NetworkManager::sendData(data, data.getDataSize());
    // }
    return SI_TEAMSELECT;
}
SCENE_ID SceneTeam::executeCommand(int command)
{
    // if (command == NC_SERVER_2_CLIENT)
    // {
    //     Vector2f positionData[1];
    //     for(int i = 0;i < 2; i++){
    //         NetworkManager::recvData(positionData[i],sizeof(Vector2f));
    //         position[i].x += positionData[i].x;
    //         if(position[i].x == 2){
    //             position[i].x = 0;
    //         }
    //         else if(position[i].x == -1){
    //             position[i].x = 1;
    //         }
    //     }
    // }
    // else if(command == NC_SERVER_CHARASELSECT){
    //     return SI_CHARASELECT;
    // }
    return SI_TEAMSELECT;
}
void SceneTeam::draw3D()
{
}
void SceneTeam::draw2D()
{
}