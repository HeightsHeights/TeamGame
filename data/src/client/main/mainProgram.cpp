#include "./mainProgram.h"
#include "../network/network.h"
#include "../render/window/window.h"
#include "../render/shader/shaderManager.h"
#include "../controller/controllerManager.h"
#include "../scene/sceneManager.h"

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

    WindowManager *window = new WindowManager(argc, argv);
    if (window == NULL)
    {
        return -1;
    }
    if (!ShaderManager::initShader())
    {
        return -1;
    }
    if (!SceneManager::init(window))
    {
        return -1;
    }

    SDL_Event event;

    for (int i = 0; event.type != SDL_QUIT; i++)
    {
        SDL_PollEvent(&event);
        SceneManager::drawWindow();
        SDL_Delay(1);
    }
    return 0;
}
