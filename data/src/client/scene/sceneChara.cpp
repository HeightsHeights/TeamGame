#include "./sceneChara.h"
#include "../../common/network/networkCommand.h"
#include "../../common/network/dataBlock/dataBlock.h"
#include "../network/networkManager.h"
SceneChara::SceneChara(WindowManager *window) : BaseScene(window)
{
}
bool SceneChara::init()
{
    return true;
}
SCENE_ID SceneChara::reactController(ControllerParam param)
{
    return SI_CHARA;
}
SCENE_ID SceneChara::executeCommand(int command)
{
    return SI_CHARA;
}
void SceneChara::draw3D()
{
}
void SceneChara::draw2D()
{
}