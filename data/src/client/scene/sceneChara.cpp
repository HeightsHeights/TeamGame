#include "./sceneChara.h"
#include "../../common/network/networkCommand.h"
#include "../../common/network/dataBlock/dataBlock.h"
#include "../network/networkManager.h"
SceneChara::SceneChara(WindowManager *window) : BaseScene(window)
{
}
bool SceneChara::init()
{
    position = Vector3f_ZERO;
    return true;
}
SCENE_ID SceneChara::reactController(ControllerParam param)
{
    // position.x += param.axisL.x;
    // if (position.x == 2)
    // {
    //     position.x = 0;
    // }
    // else if (position.x == -1)
    // {
    //     position.x = 1;
    // }

    // if (param.buttonDown[CT_DECITION_OR_ATTACK])
    // {
    //     DataBlock data;
    //     data.setCommand2DataBlock(NC_READY);
    //     NetworkManager::sendData(data, data.getDataSize());
    // }

    return SI_CHARASELECT;
}
SCENE_ID SceneChara::executeCommand(int command)
{
    // if (command == NC_SERVER_2_CLIENT)
    // {
    //     int num;
    //     NetworkManager::recvData(&num, sizeof(int));
    //     decision[num] = true;
    // }
    // else if (command == NC_SERVER_MAINGAME)
    // {
    //     return SI_MAIN;
    // }
    return SI_CHARASELECT;
}
void SceneChara::draw3D()
{
}
void SceneChara::draw2D()
{
}