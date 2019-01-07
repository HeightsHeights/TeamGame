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

static const SDL_Color gaRed = {0, 0, 255, 0};
SceneTitle::SceneTitle(WindowManager *window) : BaseScene(window)
{

    // static const GLfloat g_vertex_buffer_data[] = {
    //     -1.9f, -0.9f, 0.0f,
    //     0.9f, -0.9f, 0.0f,
    //     -0.9f, 0.9f, 0.0f,
    //     0.9f, 0.9f, 0.0f};

    // static const GLuint g_indice_buffer_data[] = {
    //     0, 1, 2,
    //     2, 1, 3};

    // static const GLfloat g_color_buffer_data[] = {
    //     1.0f, 0.0f, 0.0f,
    //     1.0f, 1.0f, 0.0f,
    //     0.0f, 0.0f, 1.0f,
    //     0.0f, 1.0f, 1.0f};

    // GLuint vao;
    // glGenVertexArrays(1, &vao1);
    // glBindVertexArray(vao1);
    // GLuint vertexBufferObject;
    // GLuint indexBufferObject;
    // glGenBuffers(1, &indexBufferObject);
    // glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBufferObject);
    // glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(g_indice_buffer_data), g_indice_buffer_data, GL_STATIC_DRAW);
    // glGenBuffers(1, &vertexBufferObject);
    // glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObject);
    // glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);
    // glEnableVertexAttribArray(0);
    // glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void *)0);
    // GLuint colorbuffer;
    // glGenBuffers(1, &colorbuffer);
    // glBindBuffer(GL_ARRAY_BUFFER, colorbuffer);
    // glBufferData(GL_ARRAY_BUFFER, sizeof(g_color_buffer_data), g_color_buffer_data, GL_STATIC_DRAW);
    // glEnableVertexAttribArray(1);
    // glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (void *)0);
    // glBindVertexArray(0);
}
static int num;
bool SceneTitle::init()
{
    image[0] = GuiImageLoader().load("./data/res/gui/image/title.png");
    image[1] = GuiImageLoader().load("./data/res/gui/image/google.png");
    text[0] = GuiTextLoader().load(FID_NORMAL, "TA", gaRed);
    for (int j = 0; j < 2; j++)
    {
        position[j] = Vector2f_ZERO;
    }
    for (int i = 0; i < 2; i++)
    {
        if (image[i] == NULL || text[i] == NULL)
            return false;
    }
    return true;
}
SCENE_ID SceneTitle::reactController(ControllerParam param)
{
    if (button == true)
    {
        position[0].x += param.axisL.x;
        button = false;
    }
    if (param.axisL.x == 0)
    {
        button = true;
    }

    if (position[0].x == 3)
    {
        position[0].x = 0;
    }
    else if (position[0].x == -1)
    {
        position[0].x = 1;
    }

    if (position[0].x == 1 && param.buttonDown[CT_DECITION_OR_ATTACK])
    {
        configbutton = true;
    }
    return SI_TITLE;
}
SCENE_ID SceneTitle::executeCommand(int command)
{
    return SI_TITLE;
}
void SceneTitle::draw3D()
{
}
static int i;
void SceneTitle::draw2D()
{

    ShaderManager::startShader(SID_GUI);

    if (configbutton)
    {
        i++;
        glPushMatrix();
        glScaled(i, i, 0);
        if (i > 5)
            i = 5;
        text[0]->draw();
        image[1]->draw();
        glPopMatrix();
    }
    else
    {
        i = 0;
        image[0]->draw();
    }
    ShaderManager::stopShader(SID_GUI);
    //名前変更
    // Console().scanString("YourName", config->name.c_str(), &config->name);
    // Console().scanString("ServerAddress", config->serverAddress.c_str(), &config->serverAddress);

    // ShaderManager::startShader(SID_GUI);
    // glBindVertexArray(vao1);
    // glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (void *)0);
    // glBindVertexArray(0);
    // ShaderManager::stopShader(SID_GUI);
}