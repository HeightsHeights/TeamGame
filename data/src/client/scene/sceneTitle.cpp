#include "./sceneTitle.h"
#include "../render/shader/shaderManager.h"
#include "../../common/network/networkCommand.h"
#include "../../common/network/dataBlock/dataBlock.h"
#include "../network/networkManager.h"

SceneTitle::SceneTitle(WindowManager *window) : BaseScene(window)
{
}
bool SceneTitle::init()
{
    for (int i = 0; i < 2; i++)
    {
        obj[i] = ObjModelLoader().load("data/res/gui/obj/", "test");
        if (obj[i] == NULL)
        {
            return false;
        }
        position[i] = Vector3f_ZERO;
    }

    //TestXModel *obj = TestXLoader().load("data/res/gui/x/", "sample");

    GLfloat green[] = {1.0, 1.0, 1.0, 1.0};
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, green);
    glEnable(GL_TEXTURE_2D);
    return true;
}
void SceneTitle::reactController(ControllerParam param)
{
    DataBlock data;
    NETWORK_COMMAND command = NC_CONTROLLER_INFO;
    data.setData(&command, sizeof(NETWORK_COMMAND));
    data.setData(&param, sizeof(ControllerParam));
    NetworkManager::sendData(data, data.getDataSize());
}
SCENE_ID SceneTitle::executeCommand(int command)
{
    if (command == NC_SERVER_2_CLIENT)
    {
        Vector3f positionData[2];

        for (int i = 0; i < 2; i++)
        {
            NetworkManager::recvData(positionData[i], sizeof(Vector3f));
            position[i].x = positionData[i].x;
            position[i].z = positionData[i].z;
        }
    }
    return SI_TITLE;
}
void SceneTitle::drawWindow()
{
    GLfloat light0pos[] = {5.0, 8.0, 3.0, 1.0};
    window->clearWindow();
    glLoadIdentity();
    gluPerspective(60.0, (double)WINDOW_WIDTH / (double)WINDOW_HEIGHT, 1.0, 100.0);
    gluLookAt(5.0, 8.0, 12.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
    glLightfv(GL_LIGHT0, GL_POSITION, light0pos);

    ShaderManager::startShader(SID_STATIC);
    for (int i = 0; i < 2; i++)
    {
        glPushMatrix();
        glTranslated(position[i].x, position[i].y, position[i].z);
        obj[i]->draw();
        glPopMatrix();
    }
    ShaderManager::stopShader(SID_STATIC);

    glFlush();
    window->swapWindow();
}