#include "./sceneTitle.h"
#include "../render/shader/shaderManager.h"
#include "../../common/network/networkCommand.h"
#include "../../common/network/dataBlock/dataBlock.h"
#include "../network/networkManager.h"
#include "../../common/math/quat/quat.h"
#include "../../common/math/angle/angle.h"
#include "../../common/math/matrix/matrixSet.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

SceneTitle::SceneTitle(WindowManager *window) : BaseScene(window)
{
}
bool SceneTitle::init()
{
    // for(int i = 0;i < 2; i++){
    //     position[i] = Vector3f_ZERO;
    // }
    return true;
}
SCENE_ID SceneTitle::reactController(ControllerParam param)
{
    // DataBlock data;
    // NETWORK_COMMAND command = NC_CONTROLLER_INFO;
    // data.setData(&command, sizeof(NETWORK_COMMAND));
    // data.setData(&param, sizeof(ControllerParam));
    // NetworkManager::sendData(data, data.getDataSize());
    return SI_TITLE;
}
SCENE_ID SceneTitle::executeCommand(int command)
{
    // if (command == NC_SERVER_2_CLIENT)
    // {
    //     Vector3f positionData[2];
    //     for(int i = 0;i < 2; i++){
    //     NetworkManager::recvData(positionData[i],sizeof(Vector3f));
    //     position[i].x = positionData[i].x;
    //     position[i].z = positionData[i].z;
    //     }
    // }
    return SI_TITLE;
}
void SceneTitle::draw3D()
{
}
void SceneTitle::draw2D()
{
}