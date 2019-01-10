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
    mush = ObjModelLoader().load("./data/res/gui/obj/kinokochara/", "kinokochara");

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
    positionMush += Vector2f(param.axisL.x, param.axisL.y);
    return SI_MAIN;
}
SCENE_ID SceneMainGame::executeCommand(int command)
{
    return SI_MAIN;
}
void SceneMainGame::draw3D()
{
    float lightPos[] = {0, 50, 0, 1};
    glLightfv(GL_LIGHT0, GL_POSITION, lightPos);

    gluPerspective(60, WINDOW_WIDTH / WINDOW_HEIGHT, 1.0, 100);
    gluLookAt(0 + positionMush.x, 50, 30 + positionMush.y, positionMush.x, 0, positionMush.y, 0, 1, 0);

    ShaderManager::startShader(SID_STATIC);

    glPushMatrix();
    glScalef(10.0f, 1.0f, 10.0f);
    tile->draw();
    glPopMatrix();

    glPushMatrix();
    glScalef(1.0f, 2.0f, 1.0f);
    glTranslatef(positionMush.x, 0, positionMush.y);
    mush->draw();
    glPopMatrix();

    ShaderManager::stopShader(SID_STATIC);
}
void SceneMainGame::draw2D()
{
    ShaderManager::startShader(SID_GUI);
    GuiRect dst = GuiRect(0.0, 0.0, 100, 200);
    imageNumber[1]->draw(NULL, &dst, 0.5f);
    ShaderManager::stopShader(SID_GUI);
}