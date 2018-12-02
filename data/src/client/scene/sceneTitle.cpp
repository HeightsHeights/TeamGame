#include "./sceneTitle.h"
#include "../render/shader/shaderManager.h"

SceneTitle::SceneTitle(WindowManager *window) : BaseScene(window)
{
}
bool SceneTitle::init()
{
    obj = ObjModelLoader().load("data/res/gui/obj/", "test");
    if (obj == NULL)
    {
        return false;
    }

    //TestXModel *obj = TestXLoader().load("data/res/gui/x/", "sample");

    GLfloat green[] = {1.0, 1.0, 1.0, 1.0};
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, green);
    glEnable(GL_TEXTURE_2D);
    return true;
}
void SceneTitle::reactController()
{
}
void SceneTitle::executeCommand()
{
}
void SceneTitle::drawWindow()
{
    GLfloat light0pos[] = {5.0, 8.0, 3.0, 1.0};
    window->clearWindow();
    glLoadIdentity();
    gluPerspective(60.0, (double)WINDOW_WIDTH / (double)WINDOW_HEIGHT, 1.0, 100.0);
    gluLookAt(5.0, 8.0, 12.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
    glLightfv(GL_LIGHT0, GL_POSITION, light0pos);
    glPushMatrix();
    ShaderManager::startShader(SID_STATIC);
    glRotated(0, 0, 1, 0);

    obj->draw();
    ShaderManager::stopShader(SID_STATIC);
    glPopMatrix();
    glFlush();
    window->swapWindow();
}