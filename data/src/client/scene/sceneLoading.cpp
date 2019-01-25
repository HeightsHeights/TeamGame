#include "./sceneLoading.h"
#include "../render/shader/shaderManager.h"
#include "../../common/network/networkCommand.h"
#include "../../common/network/dataBlock/dataBlock.h"
#include "../network/networkManager.h"
#include "../audio/audioManager.h"
#include "../controller/controllerManager.h"
#include "../main/threadManager.h"

#define PNG_DIR_PATH "./data/res/gui/image/"
#define PNG_FILE_EXTENSION ".png"

SceneLoading::SceneLoading(WindowManager *window) : BaseScene(window)
{
}
SceneLoading::SceneLoading(WindowManager *window, ConfigData *config) : BaseScene(window, config)
{
}
bool SceneLoading::init()
{
    count = 0;
    std::string numbersNameTemplate = "loading/";
    for (int i = 0; i < ANIME_NUMBER; i++)
    {
        char numberString[4];
        sprintf(numberString, "%d", i);
        std::string imageName = numbersNameTemplate + std::string(numberString);
        image[i] = GuiImageLoader().load((PNG_DIR_PATH + imageName + PNG_FILE_EXTENSION).c_str());
        if (image[i] == NULL)
        {
            return false;
        }
    }
    return true;
}
SCENE_ID SceneLoading::reactController(ControllerParam param)
{
#ifndef _UNENABLE_NETWORK
    if (!NetworkManager::connect())
    {
        fprintf(stderr, "Error --> NetworkManager::connect()\n");
    }
    else
    {
        const char *myname;
        char name[256];
        myname = config->name.c_str();
        if (strlen(myname) < 256)
            strcpy(name, myname);
        DataBlock data;
        data.setCommand2DataBlock(NC_START);
        data.setData(&name, sizeof(char *));
        NetworkManager::sendData(data, data.getDataSize());
    }
    if (!ThreadManager::start(ThreadManager::networkThread, "networkThread"))
    {
        fprintf(stderr, "Error --> ThreadManager::start()\n");
    }
#endif
    return SI_LOADING;
}
SCENE_ID SceneLoading::executeCommand(int command)
{
    return SI_LOADING;
}
void SceneLoading::draw3D()
{
}
void SceneLoading::draw2D()
{
    ShaderManager::startShader(SID_GUI);
    image[ANIME_0]->draw(NULL, NULL);
    count++;
    if (count > 7)
    {
        count = 0;
    }
    SDL_Delay(100);
    ShaderManager::stopShader(SID_GUI);
}