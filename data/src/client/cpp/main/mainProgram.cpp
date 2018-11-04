#include "../../header/main/mainProgram.h"
#include "../../header/render/window.h"
#include "../../header/render/shader.h"
#include "../../header/render/rawmodel.h"

/******************************************************************************
 * メイン関数
******************************************************************************/
int main(int argc, char *argv[])
{
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER | SDL_INIT_AUDIO | SDL_INIT_JOYSTICK))
    {
        fprintf(stderr, "Error --> SDL_Init()\n");
        return -1;
    }

    WindowManager window(argc, argv);
    
    window.clearWindow();
    ShaderManager::startShader();
    glColor3f(0.0, 0.0, 0.0);
    glBegin(GL_POLYGON);
    glVertex2d(-0.9, -0.9);
    glVertex2d(0.9, -0.9);
    glVertex2d(0.9, 0.9);
    glVertex2d(-0.9, 0.9);
    glEnd();
    ShaderManager::stopShader();

    window.swapWindow();
    SDL_Delay(1000);

    return 0;
}
