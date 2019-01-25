#include "./sceneLoading.h"
#include "../render/shader/shaderManager.h"
#include "../../common/network/networkCommand.h"
#include "../../common/network/dataBlock/dataBlock.h"
#include "../network/networkManager.h"
#include "../audio/audioManager.h"
#include "../controller/controllerManager.h"
#include "../render/gui/sprite/guiSpriteLoader.h"

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
    clockCounter = RingCounter(0, 0, 30 * 2 - 1);
    loadingCounter = RingCounter(0, 0, 4 * 10 - 1);

    background = GuiImageLoader().load((PNG_DIR_PATH + std::string("configbg") + PNG_FILE_EXTENSION).c_str());

    const std::string loadingMessageName[] = {
        "Now Loading   ",
        "Now Loading.  ",
        "Now Loading.. ",
        "Now Loading...",
    };

    const SDL_Color black = {0, 0, 0, 0};
    for (int i = 0; i < 4; i++)
    {
        loadingMessageText[i] = GuiTextLoader().load(FID_NORMAL, loadingMessageName[i].c_str(), black);
    }

    std::string numbersNameTemplate = "effect/loading/frame-";
    for (int i = 0; i < 30; i++)
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

    background->draw(0, NULL);

    GuiRect dst = {-50, 150, 100, 100};
    image[clockCounter.getCount() / 2]->draw(NULL, &dst);
    ++clockCounter;

    dst = {-100, 0, 200, 40};
    loadingMessageText[loadingCounter.getCount() / 10]->draw(NULL, &dst);
    ++loadingCounter;

    ShaderManager::stopShader(SID_GUI);
}