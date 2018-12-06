#include "./sceneTitle.h"
#include "../render/shader/shaderManager.h"
#include "../../common/network/networkCommand.h"
#include "../../common/network/dataBlock/dataBlock.h"
#include "../network/networkManager.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

SceneTitle::SceneTitle(WindowManager *window) : BaseScene(window)
{
}
bool SceneTitle::init()
{
    glEnable(GL_TEXTURE_2D);
    SDL_Surface *surface = IMG_Load("./data/res/gui/obj/cube/test2_a.png");
    if (!surface)
    {
        return false;
    }
    SDL_Texture *texture = SDL_CreateTextureFromSurface(window->getRenderer(), surface);
    glGenTextures(1, &texId);
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    glBindTexture(GL_TEXTURE_2D, texId);
    int Mode = GL_RGB;
    if (surface->format->BytesPerPixel == 4)
    {
        Mode = GL_RGBA;
    }

    glTexImage2D(GL_TEXTURE_2D, 0, Mode, surface->w, surface->h, 0, Mode, GL_UNSIGNED_BYTE, surface->pixels);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glBindTexture(GL_TEXTURE_2D, 0);

    GLfloat green[] = {1.0, 1.0, 1.0, 1.0};
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, green);

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
    glClearDepth(1.0);
    ShaderManager::startShader(SID_GUI);

    GLfloat light0pos[] = {0.0, 0.0, 0.0, 1.0};
    glLightfv(GL_LIGHT0, GL_POSITION, light0pos);

    float vertexPosition[] = {
        0.5f, 0.5f,
        -0.5f, 0.5f,
        -0.5f, -0.5f,
        0.5f, -0.5f};

   
    const GLfloat vertexUv[] = {
        1,
        0,
        0,
        0,
        0,
        1,
        1,
        1,
    };
    int positionLocation = glGetAttribLocation(42, "position");
    int uvLocation = glGetAttribLocation(42, "uv");
    int textureLocation = glGetUniformLocation(42, "texture");

    // attribute属性を有効にする
    glEnableVertexAttribArray(positionLocation);
    glEnableVertexAttribArray(uvLocation);

    // uniform属性を設定する
    glUniform1i(textureLocation, 0);

    // attribute属性を登録
    glVertexAttribPointer(positionLocation, 2, GL_FLOAT, false, 0, vertexPosition);
    glVertexAttribPointer(uvLocation, 2, GL_FLOAT, false, 0, vertexUv);

    glBindTexture(GL_TEXTURE_2D, texId);
    glDrawArrays(GL_TRIANGLE_FAN, 0, 4);

    ShaderManager::stopShader(SID_GUI);

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