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
SceneTitle::SceneTitle(WindowManager *window) : BaseScene(window)
{

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
    obj2 = ObjModelLoader().load("data/res/gui/obj/", "test");
    model = XLoader().load("data/res/gui/x/", "sample");
    int textureLocation = glGetUniformLocation(45, "texture");
    glUniform1i(textureLocation, 0);
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

    // glEnable(GL_TEXTURE_2D);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_BLEND);
    glAlphaFunc(GL_GREATER, 0.5);
    // glEnable(GL_ALPHA_TEST);
    glPushMatrix();
    glLoadIdentity();
    GLfloat light0pos[] = {0.0, 0.0, 0.0, 1.0};
    glLightfv(GL_LIGHT0, GL_POSITION, light0pos);
    gluPerspective(60.0, (double)WINDOW_WIDTH / (double)WINDOW_HEIGHT, 1.0, 100.0);
    gluLookAt(5.0, 8.0, 12.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
    // gluLookAt(0.0, 0.0, 12.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
    angle += 1;
    // glTranslatef(angle / 50, 0.0, 0.0);
    // glRotated(angle, 0, 1, 1);
    // glDepthMask(GL_FALSE);
    // ShaderManager::startShader(SID_RED);
    // obj->draw();
    // ShaderManager::stopShader(SID_RED);
    ShaderManager::startShader(SID_RED);
    // glTranslatef(-1.0, -3, -6);
    obj2->draw();
    ShaderManager::stopShader(SID_RED);
    glDisable(GL_LIGHTING);
    glPushMatrix();
    // glLoadIdentity();
    glColor4d(1.0, 0.0, 0.0, 1.0);
    glBegin(GL_POLYGON);
    glVertex3d(-2.0, -2.0, -5.0);
    glVertex3d(2.0, -2.0, -5.0);
    glVertex3d(2.0, 2.0, -5.0);
    glVertex3d(-2.0, 2.0, -5.0);
    glEnd();
    glPopMatrix();
    // glDepthMask(GL_TRUE);
    glPopMatrix();
    // glDisable(GL_ALPHA_TEST);
    glDisable(GL_DEPTH_TEST);
    glDisable(GL_LIGHTING);

    // glClear(GL_COLOR_BUFFER_BIT);

    // glDisable(GL_TEXTURE_2D);
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
    glFlush();
    window->swapWindow();
}