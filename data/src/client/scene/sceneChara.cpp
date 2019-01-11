#include "./sceneChara.h"
#include "../render/shader/shaderManager.h"
#include "../../common/network/networkCommand.h"
#include "../../common/network/dataBlock/dataBlock.h"
#include "../network/networkManager.h"

#define PNG_DIR_PATH "./data/res/gui/image/"

SceneChara::SceneChara(WindowManager *window) : BaseScene(window)
{
}
SceneChara::SceneChara(WindowManager *window, ConfigData *config) : BaseScene(window, config)
{
}
bool SceneChara::init()
{
    std::string IMAGE_NAME[IMAGE_NUMBER] =
        {
            "configbg.png",
            "bamboo.png",
            "mushroom.png",
            "ready.png",
        };
    dst[IMAGE_BAMBOO] = GuiRect(-500,-150,200,50);
    dst[IMAGE_READY] = GuiRect(-150,-225,300,100);
    for (int i = 0; i < IMAGE_NUMBER; i++)
    {
        image[i] = GuiImageLoader().load((PNG_DIR_PATH + IMAGE_NAME[i]).c_str());
        if (image[i] == NULL)
        {
            return false;
        }
    }
    return true;
}
SCENE_ID SceneChara::reactController(ControllerParam param)
{
    if (button == true)
    {
        if (position.y == 0){
            position.x += param.axisL.x;
        }
        position.y += param.axisL.y;
        button = false;
    }
    if (param.axisL.x == 0 && param.axisL.y == 0)
    {
        button = true;
    }

    if (position.x > 1)
    {
        position.x = 0;
    }
    else if (position.x < 0)
    {
        position.x = 1;
    }

    if (position.y > 1)
    {
        position.y = 1;
    }
    else if (position.y < 0)
    {
        position.y = 0;
    }

    if (position.y == 1 && param.buttonDown[CT_DECITION_OR_ATTACK] && !param.buttonState[CT_DECITION_OR_ATTACK])
    {
        DataBlock data;
        data.setCommand2DataBlock(NC_READY);
        NetworkManager::sendData(data, data.getDataSize());
    }
    else if (position.y == 1 && param.buttonDown[CT_CANCEL] && !param.buttonState[CT_CANCEL])
    {
        DataBlock data;
        data.setCommand2DataBlock(NC_CANCEL);
        NetworkManager::sendData(data, data.getDataSize());
    }
    // else
    // {
    //     DataBlock data;
    //     data.setCommand2DataBlock(NC_CONNECT);
    //     NetworkManager::sendData(data, data.getDataSize());
    // }

    return SI_CHARASELECT;
}
SCENE_ID SceneChara::executeCommand(int command)
{
    if (command == NC_SERVER_READY)
    {
        int num;
        NetworkManager::recvData(&num, sizeof(int));
        decision[num] = true;
    }
    else if (command == NC_SERVER_CANCEL)
    {
        int num;
        NetworkManager::recvData(&num, sizeof(int));
        decision[num] = false;
    }
    else if (command == NC_SERVER_MAINGAME)
    {
        return SI_MAIN;
    }
    else if (command == NC_SERVER_2_CLIENT)
    {
        NetworkManager::recvData(&playernum, sizeof(int));
        connect[playernum] = true;
    }
    return SI_CHARASELECT;
}
void SceneChara::draw3D()
{
}
void SceneChara::draw2D()
{
    if(position.y == 0){
        bright = 0.3f;
    }
    else{
        bright = 1.0f;
    }
    ShaderManager::startShader(SID_GUI);
    image[IMAGE_CONFIGBG]->draw(NULL, NULL, 1);
    image[IMAGE_READY]->draw(NULL, &dst[IMAGE_READY], bright);
    image[(int)IMAGE_BAMBOO + (int)position.x]->draw(NULL, &dst[IMAGE_BAMBOO]);
    ShaderManager::stopShader(SID_GUI);
}