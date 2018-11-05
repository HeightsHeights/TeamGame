#include "../../header/main/mainProgram.h"
#include "../../header/network/network.h"
#include "../../header/render/window.h"
#include "../../header/render/shader.h"
#include "../../header/render/rawmodel.h"
#define WINDOW_WIDTH 1280
#define WINDOW_HEIGHT 720
/******************************************************************************
 * メイン関数
******************************************************************************/
int main(int argc, char *argv[])
{
    char localHostName[] = "localhost";
    char *serverName;

    /* コマンド引数確認 */
    if (argc == 1)
    {
        serverName = localHostName;
    }
    else if (argc == 2)
    {
        serverName = argv[1];
    }
    else
    {
        fprintf(stderr, "Usage: %s, Cannot find a Server Name.\n", argv[0]);
        return -1;
    }

    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER | SDL_INIT_AUDIO | SDL_INIT_JOYSTICK))
    {
        fprintf(stderr, "Error --> SDL_Init()\n");
        return -1;
    }
    WindowManager window = *new WindowManager(argc, argv);
    ShaderManager::initShader();
    RawModel model = ModelLoader().loadFile("data/res/gui/obj/monkey.obj");

    GLfloat light0pos[] = {0.0, 5.0, 4.0, 1.0};
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

    for (int i = 0; i < 500; i++)
    {

        window.clearWindow();
        glLoadIdentity();
        gluPerspective(60.0, (double)WINDOW_WIDTH / (double)WINDOW_HEIGHT, 1.0, 100.0);
        gluLookAt(0.0, 5.0, 10.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
        glLightfv(GL_LIGHT0, GL_POSITION, light0pos);
        glPushMatrix();
        ShaderManager::startShader();
        glRotated(i, 0, 1, 0);
        model.drawModel();
        ShaderManager::stopShader();
        glPopMatrix();
        glFlush();
        window.swapWindow();
        SDL_Delay(1);
    }
    return 0;
}
