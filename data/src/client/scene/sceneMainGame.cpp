#include "./sceneMainGame.h"

SceneMainGame::SceneMainGame(WindowManager *window) : BaseScene(window)
{
}
bool SceneMainGame::init()
{
    return true;
}
void SceneMainGame::reactController()
{
}
SCENE_ID SceneMainGame::executeCommand()
{
    return SI_MAIN;
}
void SceneMainGame::drawWindow()
{
}