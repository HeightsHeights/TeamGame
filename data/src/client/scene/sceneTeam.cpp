#include "./sceneTeam.h"

SceneTeam::SceneTeam(WindowManager *window) : BaseScene(window)
{
}
bool SceneTeam::init()
{
    return true;
}
SCENE_ID SceneTeam::reactController(ControllerParam param)
{
    return SI_TEAM;
}
SCENE_ID SceneTeam::executeCommand(int command)
{
    return SI_TEAM;
}
void SceneTeam::draw3D()
{
}
void SceneTeam::draw2D()
{
}