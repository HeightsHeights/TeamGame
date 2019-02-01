#include "./sceneBase.h"

#include <GL/gl.h>
BaseScene::BaseScene(WindowManager *window)
{
    this->myId = 0;
    this->window = window;
}
BaseScene::BaseScene(WindowManager *window, ConfigData *config)
{
    this->myId = 0;
    this->window = window;
    this->config = config;
}
bool BaseScene::init()
{
}
SCENE_ID BaseScene::reactController(ControllerParam param)
{
}
SCENE_ID BaseScene::executeCommand(int command)
{
}
void BaseScene::drawWindow()
{
    window->clearWindow();
    drawBackground();
    glEnable(GL_LIGHTING);
    glEnable(GL_DEPTH_TEST);
    glPushMatrix();
    glLoadIdentity();
    draw3D();
    glPopMatrix();

    glDisable(GL_LIGHTING);
    glDisable(GL_DEPTH_TEST);
    glPushMatrix();
    glLoadIdentity();
    draw2D();
    glPopMatrix();
    window->swapWindow();
}
void BaseScene::drawBackground()
{
}
void BaseScene::draw3D()
{
}
void BaseScene::draw2D()
{
}