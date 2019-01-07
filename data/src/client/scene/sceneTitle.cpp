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

static const SDL_Color gWhite = {255, 255, 255, 255};
SceneTitle::SceneTitle(WindowManager *window) : BaseScene(window)
{
    image = GuiImageLoader().load("./data/res/gui/image/google.png");
    //image2 = GuiImageLoader().load("./data/res/gui/image/kuro.png");
    text = GuiTextLoader().load(FID_NORMAL, "config", gWhite);
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
bool SceneTitle::init()
{
    position = Vector2f_ZERO;
    return true;
}
SCENE_ID SceneTitle::reactController(ControllerParam param)
{
    if (button == true)
    {
        position.x += param.axisL.x;
        button = false;
    }
    //printf("%f\n",position.x);
    if (param.axisL.x == 0)
    {
        button = true;
    }

    if (position.x == 3)
    {
        position.x = 0;
    }
    else if (position.x == -1)
    {
        position.x = 1;
    }

    if (position.x == 1 && param.buttonDown[CT_DECITION_OR_ATTACK])
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
        if (i > 10)
            i = 10;
        //image2->draw();
        glPopMatrix();
    }
    else
    {
        image->draw();
    }
    ShaderManager::stopShader(SID_GUI);

    // ShaderManager::startShader(SID_GUI);
    // glBindVertexArray(vao1);
    // glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (void *)0);
    // glBindVertexArray(0);
    // ShaderManager::stopShader(SID_GUI);
}