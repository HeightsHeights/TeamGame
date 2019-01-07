#include "./sceneMainGame.h"

#include "../render/shader/shaderManager.h"
SceneMainGame::SceneMainGame(WindowManager *window) : BaseScene(window)
{
    tile = ObjModelLoader().load("./data/res/gui/obj/", "tile");
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
void SceneMainGame::draw3D()
{
    gluPerspective(60, WINDOW_WIDTH / WINDOW_HEIGHT, 1.0, 100);
    gluLookAt(0, 20, 1, 0, 0, 0, 0, 1, 0);
    ShaderManager::startShader(SID_STATIC);
    tile->draw();
    ShaderManager::stopShader(SID_STATIC);
}
void SceneMainGame::draw2D()
{
}