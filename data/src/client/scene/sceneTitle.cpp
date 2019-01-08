#include "./sceneTitle.h"
#include "../render/shader/shaderManager.h"
#include "../../common/network/networkCommand.h"
#include "../../common/network/dataBlock/dataBlock.h"
#include "../network/networkManager.h"
#include "../../common/math/quat/quat.h"
#include "../../common/math/angle/angle.h"
#include "../../common/math/matrix/matrix4f.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
GLuint vertexBufferObject;
GLuint posBufferObject;
GLuint colorbuffer;
GLuint uvbuffer;
int R = 1000;
GLfloat position_data[2000];
GLfloat g_color_buffer_data[3000];
float x[2000];
SceneTitle::SceneTitle(WindowManager *window) : BaseScene(window)
{
    static const GLfloat g_vertex_buffer_data[] = {
        -1.000000, -1.000000, 0.000000,
        1.000000, -1.000000, 0.000000,
        -1.000000, 1.000000, 0.00000,
        1.000000, 1.000000, 0.000000};

    static const GLuint g_indice_buffer_data[] = {
        0, 1, 2,
        2, 1, 3};

    static const GLfloat uv_buffer_date[]{
        0.4f, 0.6f,
        0.6f, 0.6f,
        0.4f, 0.4f,
        0.6f, 0.4f};

    for (int i = 0; i < R; i++)
    {
        // float x = rand() % 201 - 100;
        // x /= 10;
        position_data[i] = 0;
    }

    for (int i = 0; i < R; i++)
    {
        // float x = (rand() % 1000);
        // x /= 1000;
        g_color_buffer_data[i] = 0.5;
    }
    GLuint vao;
    glGenVertexArrays(1, &vao123);
    glBindVertexArray(vao123);

    GLuint indexBufferObject;
    glGenBuffers(1, &indexBufferObject);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBufferObject);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6 * sizeof(unsigned int), g_indice_buffer_data, GL_STATIC_DRAW);
    glGenBuffers(1, &vertexBufferObject);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObject);
    glBufferData(GL_ARRAY_BUFFER, 4 * sizeof(Vector3f), g_vertex_buffer_data, GL_STATIC_DRAW);
    // glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(sub_buffer_data), sub_buffer_data);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void *)0);
    glGenBuffers(1, &posBufferObject);
    glBindBuffer(GL_ARRAY_BUFFER, posBufferObject);
    glBufferData(GL_ARRAY_BUFFER, R * 2 * sizeof(GLfloat), position_data, GL_STREAM_DRAW);
    glBufferSubData(GL_ARRAY_BUFFER, 0, R * 2 * sizeof(GLfloat), position_data);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (void *)0);
    glGenBuffers(1, &colorbuffer);
    glBindBuffer(GL_ARRAY_BUFFER, colorbuffer);
    glBufferData(GL_ARRAY_BUFFER, R * 3 * sizeof(GLfloat), g_color_buffer_data, GL_STREAM_DRAW);
    glBufferSubData(GL_ARRAY_BUFFER, 0, R * 3 * sizeof(GLfloat), g_color_buffer_data);
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, (void *)0);
    glGenBuffers(1, &uvbuffer);
    glBindBuffer(GL_ARRAY_BUFFER, uvbuffer);
    glBufferData(GL_ARRAY_BUFFER, 4 * sizeof(Vector2f), uv_buffer_date, GL_STATIC_DRAW);
    glEnableVertexAttribArray(3);
    glVertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, 0, (void *)0);

    glVertexAttribDivisor(0, 0);
    glVertexAttribDivisor(1, 1);
    glVertexAttribDivisor(2, 1);
    glVertexAttribDivisor(3, 0);

    SDL_Surface *skybox = IMG_Load("data/res/gui/image/google.png");
    // for (int i = 0; i < 6; i++)
    // {
    glGenTextures(1, &sky);
    glBindTexture(GL_TEXTURE_2D, sky);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, skybox->w, skybox->h, 0, GL_RGBA, GL_UNSIGNED_BYTE, skybox->pixels);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glBindTexture(GL_TEXTURE_2D, 0);
    // }

    glBindVertexArray(0);

    // float a[] = {
    //     3, 1, 1, 2,
    //     5, 1, 3, 4,
    //     2, 0, 1, 0,
    //     1, 3, 2, 1};
    // Matrix4x4f mat(a);
    // mat.callMe();

    // Matrix4x4f *invMat = mat.getInverseMatrix();
    // if (invMat != NULL)
    // {
    //     invMat->callMe();
    // }

    // printf("%4f\n", mat.determinant());

    obj = ObjModelLoader().load("data/res/gui/obj/cube/", "cube");
    obj2 = ObjModelLoader().load("data/res/gui/obj/", "bow");
    // model = XLoader().load("data/res/gui/x/", "sample");
    // int textureLocation = glGetUniformLocation(45, "texture");
    // glUniform1i(textureLocation, 0);
    angle = 0;

    SDL_Surface *strings;
    SDL_Color black = {0xff, 0x00, 0x00};
    TTF_Init();
    TTF_Font *font = TTF_OpenFont("data/res/gui/image/TakaoMincho.ttf", 24);
    glGenTextures(1, &texID2);
    glBindTexture(GL_TEXTURE_2D, texID2);
    strings = TTF_RenderUTF8_Blended(font, "ティーえー!#$", black);
    // SDL_Texture *texture = SDL_CreateTextureFromSurface(window->getRenderer(), strings);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, strings->w, strings->h, 0, GL_RGBA, GL_UNSIGNED_BYTE, strings->pixels);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glBindTexture(GL_TEXTURE_2D, 0);

    for (int i = 0; i < 2000; i++)
    {
        x[i] = rand() % 501;
        x[i] /= 2000;
    }
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
float y = 0.5;

void SceneTitle::drawWindow()
{

    y -= 9.8 * 0.001;
    for (int i = 0; i < 2000; i++)
    {

        switch (i % 4)
        {
        case 0:
            position_data[i] += x[i];
            // if (x > 500)
            //     position_data[i] -= 0.1;
            break;
        case 1:
            position_data[i] += (y + x[i]);
            break;
        case 2:
            position_data[i] -= x[i];
            break;
        case 3:
            position_data[i] += (y + x[i]);
            break;
        }
        // if (x > 500)
        //     position_data[i] += 0.5;
        // else
        //     position_data[i] -= 0.5;
    }
    for (int i = 0; i < 3000; i++)
        if (i % 4 == 3)
            g_color_buffer_data[i] = 0.5;

    window->clearWindow();
    // glEnable(GL_TEXTURE_2D);
    glEnable(GL_DEPTH_TEST);
    // glEnable(GL_LIGHTING);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_BLEND);
    glAlphaFunc(GL_GREATER, 0.5);
    // glEnable(GL_ALPHA_TEST);
    glPushMatrix();
    // glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
    glLoadIdentity();
    GLfloat light0pos[] = {0.0, 0.0, 0.0, 1.0};
    glLightfv(GL_LIGHT0, GL_POSITION, light0pos);
    gluPerspective(60.0, (double)WINDOW_WIDTH / (double)WINDOW_HEIGHT, 1.0, 100.0);
    gluLookAt(0.0, 0.0, 25.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
    // glOrtho(-WINDOW_WIDTH / 200.0, WINDOW_WIDTH / 200.0, -WINDOW_WIDTH / 200.0, WINDOW_HEIGHT / 200.0, -1.0, 1.0);

    // gluLookAt(5.0, 8.0, 12.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
    angle++;
    // glTranslatef(angle / 50, 0.0, 0.0);
    // glRotated(angle, 0, 1, 1);
    // glDepthMask(GL_FALSE);
    // ShaderManager::startShader(SID_RED);
    // obj->draw();
    // ShaderManager::stopShader(SID_RED);
    // ShaderManager::startShader(SID_STATIC);
    // // glTranslatef(-1.0, -3, -6);
    // obj2->draw();
    // ShaderManager::stopShader(SID_STATIC);
    glPushMatrix();
    // glScalef(3.0f, 3.0, 3.0f);
    ShaderManager::startShader(SID_PART);
    glBindTexture(GL_TEXTURE_2D, sky);
    glBindVertexArray(vao123);
    glBindBuffer(GL_ARRAY_BUFFER, posBufferObject);
    glBufferSubData(GL_ARRAY_BUFFER, 0, R * 2 * sizeof(GLfloat), position_data);
    glBindBuffer(GL_ARRAY_BUFFER, colorbuffer);
    glBufferSubData(GL_ARRAY_BUFFER, 0, R * 3 * sizeof(GLfloat), g_color_buffer_data);

    glDrawElementsInstanced(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (void *)0, R);
    glBindVertexArray(0);
    glBindTexture(GL_TEXTURE_2D, 0);
    ShaderManager::stopShader(SID_PART);
    // glPopMatrix();
    // glDepthMask(GL_TRUE);
    glPopMatrix();
    // glDisable(GL_ALPHA_TEST);
    // glDisable(GL_DEPTH_TEST);
    glDisable(GL_LIGHTING);

    // glClear(GL_COLOR_BUFFER_BIT);

    // glBindTexture(GL_TEXTURE_2D, sky[0]);
    // glEnable(GL_TEXTURE_2D);
    // glPushMatrix();
    // glLoadIdentity();
    // // glColor4d(1.0, 0.0, 1.0, 1.0);
    // glBegin(GL_POLYGON);
    // glTexCoord2f(0.0f, 0.0f);
    // glVertex2d(-0.5, 0.5);
    // glTexCoord2f(0.0f, 1.0f);
    // glVertex2d(-0.5, -0.5);
    // glTexCoord2f(1.0f, 1.0f);
    // glVertex2d(0.5, -0.5);
    // glTexCoord2f(1.0f, 0.0f);
    // glVertex2d(0.5, 0.5);
    // glEnd();
    // glPopMatrix();
    // glDisable(GL_TEXTURE_2D);
    // glBindTexture(GL_TEXTURE_2D, 0);
    // glDisable(GL_TEXTURE_2D);
    // glPushMatrix();

    // glBindTexture(GL_TEXTURE_2D, texID2);
    // glEnable(GL_TEXTURE_2D);
    // glBegin(GL_QUADS);
    // glTexCoord2f(0.0f, 0.0f);
    // glVertex3f(-0.3f, 0.3f, 0.0f);
    // glTexCoord2f(0.0f, 1.0f);
    // glVertex3f(-0.3f, -0.3f, 0.0f);
    // glTexCoord2f(1.0f, 1.0f);
    // glVertex3f(0.3f, -0.3f, 0.0f);
    // glTexCoord2f(1.0f, 0.0f);
    // glVertex3f(0.3f, 0.3f, 0.0f);
    // glEnd();
    // glDisable(GL_TEXTURE_2D);
    // glBindTexture(GL_TEXTURE_2D, 0);
    // glPopMatrix();
    glFlush();
    window->swapWindow();
}