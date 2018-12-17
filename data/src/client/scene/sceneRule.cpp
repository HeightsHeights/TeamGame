#include "./sceneRule.h"

SceneRule::SceneRule(WindowManager *window) : BaseScene(window)
{
}
bool SceneRule::init()
{
    return true;
}
SCENE_ID SceneRule::reactController(ControllerParam param)
{
    return SI_RULE;
}
SCENE_ID SceneRule::executeCommand(int command)
{
    return SI_RULE;
}
void SceneRule::draw3D()
{
}
void SceneRule::draw2D()
{
}