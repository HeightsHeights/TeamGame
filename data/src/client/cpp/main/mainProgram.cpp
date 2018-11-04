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
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER | SDL_INIT_AUDIO | SDL_INIT_JOYSTICK))
    {
        fprintf(stderr, "Error --> SDL_Init()\n");
        return -1;
    }
    serverName = localHostName;
    NetworkManager::init(serverName);
    NetworkManager::connect();
    NetworkManager::disconnect();

    return 0;
}
