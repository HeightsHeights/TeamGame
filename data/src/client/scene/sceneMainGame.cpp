#include "./sceneMainGame.h"

SceneMainGame::SceneMainGame(WindowManager *window) : BaseScene(window)
{
}
bool SceneMainGame::init()
{
    return true;
}
SCENE_ID SceneMainGame::reactController(ControllerParam param)
{
    return SI_MAIN;
}
SCENE_ID SceneMainGame::executeCommand(int command)
{
    return SI_MAIN;
}
void SceneMainGame::drawWindow()
{
}