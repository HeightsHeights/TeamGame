#include "./sceneMainGame.h"

SceneMainGame::SceneMainGame(WindowManager *window) : BaseScene(window)
{
}
bool SceneMainGame::init()
{
    return true;
}
void SceneMainGame::reactController(ControllerParam param)
{
}
SCENE_ID SceneMainGame::executeCommand(int command)
{
    return SI_MAIN;
}
void SceneMainGame::drawWindow()
{
}