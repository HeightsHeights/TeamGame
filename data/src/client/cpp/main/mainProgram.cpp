#include "../../header/main/mainProgram.h"
#include "../../header/network/network.h"
#include "../../header/render/window.h"
#include "../../header/render/shader.h"
#include "../../header/render/rawmodel.h"

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

    WindowManager window = *new WindowManager(argc,argv);
    ShaderManager::initShader();
    RawModel model = ModelLoader().loadFile("data/res/gui/obj/mononoke.obj");
    
    
    window.clearWindow();
    glLoadIdentity();
    gluLookAt(0.0, 10.0,30.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
    glPushMatrix();
    ShaderManager::startShader();
    model.drawModel();
    ShaderManager::stopShader();
    glPopMatrix();
    window.swapWindow();
    SDL_Delay(1000);



    return 0;
}
