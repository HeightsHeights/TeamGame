#include "./sceneLoading.h"
#include "../render/shader/shaderManager.h"
#include "../../common/network/networkCommand.h"
#include "../../common/network/dataBlock/dataBlock.h"
#include "../network/networkManager.h"
#include "../audio/audioManager.h"
#include "../controller/controllerManager.h"

SceneLoading::SceneLoading(WindowManager *window) : BaseScene(window)
{
}
SceneLoading::SceneLoading(WindowManager *window, ConfigData *config) : BaseScene(window, config)
{
}
bool SceneLoading::init()
{
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
}