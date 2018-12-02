#include "./mainProgram.h"
#include "../network/network.h"
#include "../render/window/window.h"
#include "../render/shader/shaderManager.h"
#include "../controller/controllerManager.h"
#include "../scene/sceneManager.h"
#include "../config/loader/configLoader.h"
/******************************************************************************
 * メイン関数
******************************************************************************/
int main(int argc, char *argv[])
{

    ConfigData *config = ConfigLoader().load("clientConfig");
    if (config == NULL)
    {
        fprintf(stderr, "Error --> ConfigLoader().load()\n");
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
        fprintf(stderr, "Error --> ShaderManager::initShader()\n");
        return -1;
    }
    if (!SceneManager::init(window))
    {
        fprintf(stderr, "Error --> SceneManager::init()\n");
        return -1;
    }
    if (!ControllerManager::init())
    {
        fprintf(stderr, "Error --> ControllerManager::init()\n");
        return -1;
    }
    SDL_atomic_t atm;
    SDL_AtomicSet(&atm, 1);

    while (SDL_AtomicGet(&atm) > 0)
    {

        if (ControllerManager::updateController())
        {
            SDL_AtomicDecRef(&atm);
        }

        SceneManager::drawWindow();
        SDL_Delay(1);
    }
    return 0;
}
