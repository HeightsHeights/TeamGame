#include "./sceneBase.h"

#include <GL/gl.h>
BaseScene::BaseScene(WindowManager *window)
{
    this->window = window;
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
    glEnable(GL_LIGHTING);
    glPushMatrix();
    glLoadIdentity();
    draw3D();
    glPopMatrix();

    glDisable(GL_LIGHTING);
    glPushMatrix();
    glLoadIdentity();
    draw2D();
    glPopMatrix();
    window->swapWindow();
}
void BaseScene::draw3D()
{
}
void BaseScene::draw2D()
{
}