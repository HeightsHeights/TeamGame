#include "./sceneChara.h"

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