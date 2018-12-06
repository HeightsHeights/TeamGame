#include "./sceneTitle.h"
#include "../render/shader/shaderManager.h"
#include "../../common/network/networkCommand.h"
#include "../../common/network/dataBlock/dataBlock.h"
#include "../network/networkManager.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

SceneTitle::SceneTitle(WindowManager *window) : BaseScene(window)
{
    //obj = ObjModelLoader().load("data/res/gui/obj/cube/", "cube");
    float vertexPosition[] = {
        0.5f, 0.5f, 0,
        0.0f, 0.5f, 0,
        0.0f, -0.5f, 0,
        0.5f, -0.5f, 0};
    unsigned int vertexIndex[] = {
        0, 1, 2,
        0, 2, 3};

    float vertexColor[] = {
        1.0, 0.0, 0.0, 1.0,
        0.0, 1.0, 0.0, 1.0,
        0.0, 0.0, 1.0, 1.0,
        1.0, 0.0, 1.0, 1.0};

    //vao bind
    glGenVertexArrays(1, &vao1);
    glBindVertexArray(vao1);

    //indexBufferObject
    GLuint ibo;
    glGenBuffers(1, &ibo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned) * 6, vertexIndex, GL_STATIC_DRAW);

    //vertexBufferObject
    GLuint vbo;
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 12, vertexPosition, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void *)0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    GLuint cbo;
    glGenBuffers(1, &cbo);
    glBindBuffer(GL_ARRAY_BUFFER, cbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 16, vertexColor, GL_STATIC_DRAW);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, (void *)0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    //unbind vao
    glBindVertexArray(0);

    float vertexPosition2[] = {
        0.0f, 0.5f, 0,
        -0.5f, 0.5f, 0,
        -0.5f, -0.5f, 0,
        0.0f, -0.5f, 0};
    unsigned int vertexIndex2[] = {
        0, 1, 2,
        0, 2, 3};
    float vertexUv[] = {
        1.0f, 0.0f,
        0.0f, 0.0f,
        0.0f, 1.0f,
        1.0f, 1.0f};
    //vao bind
    glGenVertexArrays(1, &vao2);
    glBindVertexArray(vao2);

    //indexBufferObject
    GLuint ibo2;
    glGenBuffers(1, &ibo2);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo2);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned) * 6, vertexIndex2, GL_STATIC_DRAW);

    //vertexBufferObject
    GLuint vbo2;
    glGenBuffers(1, &vbo2);
    glBindBuffer(GL_ARRAY_BUFFER, vbo2);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 12, vertexPosition2, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void *)0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    GLuint tbo2;
    glGenBuffers(1, &tbo2);
    glBindBuffer(GL_ARRAY_BUFFER, tbo2);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 8, vertexUv, GL_STATIC_DRAW);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (void *)0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glEnable(GL_TEXTURE_2D);
    SDL_Surface *surface = IMG_Load("./data/res/gui/obj/cube/test2_a.png");

    SDL_Texture *texture = SDL_CreateTextureFromSurface(window->getRenderer(), surface);
    glGenTextures(1, &texId);
    glBindTexture(GL_TEXTURE_2D, texId);
    int Mode = GL_RGB;
    if (surface->format->BytesPerPixel == 4)
    {
        Mode = GL_RGBA;
    }

    glTexImage2D(GL_TEXTURE_2D, 0, Mode, surface->w, surface->h, 0, Mode, GL_UNSIGNED_BYTE, surface->pixels);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glBindTexture(GL_TEXTURE_2D, 0);

    int uvLocation = glGetAttribLocation(45, "uv");
    int textureLocation = glGetUniformLocation(45, "texture");

    glEnableVertexAttribArray(uvLocation);

    // uniform属性を設定する
    glUniform1i(textureLocation, 0);

    //unbind vao
    glBindVertexArray(0);
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
    glClearDepth(1.0);
    GLfloat light0pos[] = {0.0, 0.0, 0.0, 1.0};
    glLightfv(GL_LIGHT0, GL_POSITION, light0pos);

    ShaderManager::startShader(SID_GUI);
    glBindVertexArray(vao1);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
    ShaderManager::stopShader(SID_GUI);

    ShaderManager::startShader(SID_RED);
    glBindVertexArray(vao2);
    glBindTexture(GL_TEXTURE_2D, texId);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
    ShaderManager::stopShader(SID_RED);

    glFlush();
    window->swapWindow();
}