#include "./sceneMainGame.h"

#include "../render/shader/shaderManager.h"

#define PNG_DIR_PATH "./data/res/gui/image/"
#define PNG_FILE_EXTENSION ".png"

SceneMainGame::SceneMainGame(WindowManager *window) : BaseScene(window)
{
}
SceneMainGame::SceneMainGame(WindowManager *window, ConfigData *config) : BaseScene(window, config)
{
}
bool SceneMainGame::init()
{
    tile = ObjModelLoader().load("./data/res/gui/obj/", "tile");
    mush = ObjModelLoader().load("./data/res/gui/obj/", "mush");

    std::string numbersNameTemplate = "numbers/number_";
    for (int i = 0; i < 10; i++)
    {
        char numberString[4];
        sprintf(numberString, "%d", i);

        std::string imageName = numbersNameTemplate + std::string(numberString) + PNG_FILE_EXTENSION;
        imageNumber[i] = GuiImageLoader().load((PNG_DIR_PATH + imageName).c_str());
    }

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
    glPushMatrix();
    tile->draw();
    glPopMatrix();
    ShaderManager::stopShader(SID_STATIC);
}
void SceneMainGame::draw2D()
{
    ShaderManager::startShader(SID_GUI);
    GuiRect dst = GuiRect(0.0, 0.0, 100, 200);
    imageNumber[1]->draw(NULL, &dst);
    ShaderManager::stopShader(SID_GUI);
}