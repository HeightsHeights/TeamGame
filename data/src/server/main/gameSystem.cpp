#include "./gameSystem.h"

#include "../scene/sceneManager.h"
#include "../../common/console/console.h"
#include "../network/networkManager.h"

bool GameSystem::init(int argc, char *argv[])
{
    int num;
    /* コマンド引数確認 */
    if (argc == 1)
    {
        num = MAX_CLIENTS;
    }
    else if (argc != 2)
    {
        fprintf(stderr, "Usage: number of clients\n");
        return false;
    }
    else if ((num = atoi(argv[1])) < 0 || num > MAX_CLIENTS)
    {
        fprintf(stderr, "clients limit = %d \n", MAX_CLIENTS);
        return false;
    }

    SDL_AtomicSet(&atm, 1);

    if (SDL_Init(SDL_INIT_TIMER))
    {
        fprintf(stderr, "Error --> SDL_Init()\n");
        return false;
    }

    if (!SceneManager::init())
    {
        fprintf(stderr, "Error --> SceneManager::init()\n");
        return false;
    }

    if (!NetworkManager::init())
    {
        fprintf(stderr, "Error --> NetworkManager::init()\n");
        return false;
    }

    return true;
}

bool GameSystem::gameLoop()
{
    while (SDL_AtomicGet(&atm) > 0)
    {
        fd_set readOK;
        if (!NetworkManager::waitRequest(&readOK))
        {
            fprintf(stderr, "Error --> NetworkManager::waitRequest()\n");
            return false;
        }
        int gClientNum = NetworkManager::getGClientNum();
        Client *gClients = NetworkManager::getGClients();

        for (int i = 0; i < gClientNum; i++)
        {
            char command;
            if (FD_ISSET(gClients[i].fd, &readOK))
            {
                NetworkManager::recvData(i, &command, sizeof(char));
                if (SceneManager::executeCommand(command, i))
                {
                    SDL_AtomicDecRef(&atm);
                }
            }
        }
    }
    return true;
}

bool GameSystem::terminate()
{
    NetworkManager::closeAll();
    return true;
}