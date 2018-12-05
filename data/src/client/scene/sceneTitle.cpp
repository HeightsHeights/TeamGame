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
        obj[i] = ObjModelLoader().load("data/res/gui/obj/kinokochara/", "kinokochara");
        if (obj[i] == NULL)
        {
            return false;
        }
    }

    //TestXModel *obj = TestXLoader().load("data/res/gui/x/", "sample");

    GLfloat green[] = {1.0, 1.0, 1.0, 1.0};
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, green);
    glEnable(GL_TEXTURE_2D);
    return true;
}
SCENE_ID SceneTitle::reactController(ControllerParam param)
{
#ifndef _UNENABLE_NETWORK
    DataBlock data;
    NETWORK_COMMAND command = NC_CONTROLLER_INFO;
    data.setData(&command, sizeof(NETWORK_COMMAND));
    data.setData(&param, sizeof(ControllerParam));
    NetworkManager::sendData(data, data.getDataSize());
#else
    position[0].x += 0.1 * param.axisL.x;
    position[0].z += 0.1 * param.axisL.y;
#endif
    return SI_TITLE;
}
SCENE_ID SceneTitle::executeCommand(int command)
{
    if (command == NC_SERVER_2_CLIENT)
    {
        Vector3f positionData[1];

        for (int i = 0; i < 2; i++)
        {
            NetworkManager::recvData(positionData[i], sizeof(Vector3f));
            dir[i] = positionData[i];
            positionData[i] *= 0.1;
            position[i].x += positionData[i].x;
            position[i].z += positionData[i].z;
        }
    }
    return SI_TITLE;
}
void SceneTitle::drawWindow()
{
    GLfloat light0pos[] = {15.0, 30.0, 3.0, 1.0};
    window->clearWindow();
    glLoadIdentity();
    gluPerspective(60.0, (double)WINDOW_WIDTH / (double)WINDOW_HEIGHT, 1.0, 100.0);
    gluLookAt(15.0, 18.0, 15.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
    glLightfv(GL_LIGHT0, GL_POSITION, light0pos);

    ShaderManager::startShader(SID_STATIC);
    for (int i = 0; i < 2; i++)
    {
        glPushMatrix();
        glTranslated(position[i].x, position[i].y, position[i].z);
        if (dir[i].x == 0 && dir[i].y == 0 && dir[i].z == 0)
        {
            dir[i] = Vector3f(1, 1, 1);
        }
        //lookAtVector(dir[i]);
        obj[i]->draw();
        glPopMatrix();
    }
    ShaderManager::stopShader(SID_STATIC);

    glFlush();
    window->swapWindow();
}

void SceneTitle::lookAtVector(Vector3f direction)
{
    direction = direction.normalize();
    Vector3f up = Vector3f(0, 1, 0);
    Vector3f cross1 = Vector3f::cross(direction, up).normalize();
    Vector3f cross2 = Vector3f::cross(cross1, direction).normalize();

    float rotation[4][4] = {{cross1.x, cross1.y, cross1.z, 0},
                            {cross2.x, cross2.y, cross2.z, 0},
                            {direction.x, direction.y, direction.z, 0},
                            {0, 0, 0, 1}};

    glMultMatrixf(rotation[0]);
}