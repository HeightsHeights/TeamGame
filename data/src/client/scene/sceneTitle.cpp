#include "./sceneTitle.h"
#include "../render/shader/shaderManager.h"
#include "../../common/network/networkCommand.h"
#include "../../common/network/dataBlock/dataBlock.h"
#include "../network/networkManager.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

SceneTitle::SceneTitle(WindowManager *window) : BaseScene(window)
{
    glEnable(GL_TEXTURE_2D);
    obj = ObjModelLoader().load("data/res/gui/obj/", "bomb");

    int textureLocation = glGetUniformLocation(45, "texture");
    glUniform1i(textureLocation, 0);
    angle = 0;
}
bool SceneTitle::init()
{
    return true;
}
SCENE_ID SceneTitle::reactController(ControllerParam param)
{
    return SI_TITLE;
}
SCENE_ID SceneTitle::executeCommand(int command)
{
    return SI_TITLE;
}
void SceneTitle::drawWindow()
{
    window->clearWindow();
    glLoadIdentity();
    GLfloat light0pos[] = {0.0, 0.0, 0.0, 1.0};
    glLightfv(GL_LIGHT0, GL_POSITION, light0pos);
    gluPerspective(60.0, (double)WINDOW_WIDTH / (double)WINDOW_HEIGHT, 1.0, 100.0);
    gluLookAt(5.0, 8.0, 12.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
    angle += 1;
    glRotated(angle, 0, 1, 1);
    ShaderManager::startShader(SID_STATIC);
    obj->draw();
    ShaderManager::stopShader(SID_STATIC);
    glFlush();
    window->swapWindow();
}