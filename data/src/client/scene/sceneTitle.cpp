#include "./sceneTitle.h"
#include "../render/shader/shaderManager.h"
#include "../../common/network/networkCommand.h"
#include "../../common/network/dataBlock/dataBlock.h"
#include "../network/networkManager.h"
#include "../../common/math/quat/quat.h"
#include "../../common/math/angle/angle.h"
#include "../../common/math/matrix/matrixSet.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

SceneTitle::SceneTitle(WindowManager *window) : BaseScene(window)
{
    static const GLfloat g_vertex_buffer_data[] = {
        -1.9f, -0.9f, 0.0f,
        0.9f, -0.9f, 0.0f,
        -0.9f, 0.9f, 0.0f,
        0.9f, 0.9f, 0.0f};

    static const GLuint g_indice_buffer_data[] = {
        0.0, 1.0, 2.0,
        2.0, 1.0, 3.0};

    static const GLfloat g_color_buffer_data[] = {
        1.0f, 0.0f, 0.0f,
        1.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 1.0f,
        0.0f, 1.0f, 1.0f};

    GLuint vao;
    glGenVertexArrays(1, &vao1);
    glBindVertexArray(vao1);
    GLuint vertexBufferObject;
    GLuint indexBufferObject;
    glGenBuffers(1, &indexBufferObject);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBufferObject);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(g_indice_buffer_data), g_indice_buffer_data, GL_STATIC_DRAW);
    glGenBuffers(1, &vertexBufferObject);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObject);
    glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void *)0);
    GLuint colorbuffer;
    glGenBuffers(1, &colorbuffer);
    glBindBuffer(GL_ARRAY_BUFFER, colorbuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(g_color_buffer_data), g_color_buffer_data, GL_STATIC_DRAW);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (void *)0);
    glBindVertexArray(0);
}
bool SceneTitle::init()
{
    // for(int i = 0;i < 2; i++){
    //     position[i] = Vector3f_ZERO;
    // }
    return true;
}
SCENE_ID SceneTitle::reactController(ControllerParam param)
{
    // DataBlock data;
    //data.setCommand2DataBlock(NC_CONTROLLER_INFO);
    // data.setData(&param, sizeof(ControllerParam));
    // NetworkManager::sendData(data, data.getDataSize());
    return SI_TITLE;
}
SCENE_ID SceneTitle::executeCommand(int command)
{
    // if (command == NC_SERVER_2_CLIENT)
    // {
    //     Vector3f positionData[2];
    //     for(int i = 0;i < 2; i++){
    //     NetworkManager::recvData(positionData[i],sizeof(Vector3f));
    //     position[i].x = positionData[i].x;
    //     position[i].z = positionData[i].z;
    //     }
    // }
    return SI_TITLE;
}
void SceneTitle::draw3D()
{
}
void SceneTitle::draw2D()
{
    ShaderManager::startShader(SID_GUI);
    glBindVertexArray(vao1);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (void *)0);
    glBindVertexArray(0);
    ShaderManager::stopShader(SID_GUI);
}