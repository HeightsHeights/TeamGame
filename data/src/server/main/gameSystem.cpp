#include "./gameSystem.h"

#include "../scene/sceneManager.h"
#include "../../common/console/console.h"
#include "../network/networkManager.h"
#include "./threadManager.h"

bool GameSystem::init(int argc, char *argv[])
{
    int num;
    /* コマンド引数確認 */
    if (argc == 1)
    {
        num = MAX_PLAYERS;
    }
    else if (argc != 2)
    {
        fprintf(stderr, "Usage: number of clients\n");
        return false;
    }
    else if ((num = atoi(argv[1])) < 0 || num > MAX_PLAYERS)
    {
        fprintf(stderr, "clients limit = %d \n", MAX_PLAYERS);
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

    if (!ThreadManager::init(&atm))
    {
        fprintf(stderr, "Error --> ThreadManager::init()\n");
        return false;
    }
    if (!ThreadManager::start(ThreadManager::dataProcessingThread, "dataProcessingThread"))
    {
        fprintf(stderr, "Error --> ThreadManager::start()\n");
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
            int command;
            if (FD_ISSET(gClients[i].fd, &readOK))
            {
                NetworkManager::recvData(i, &command, sizeof(int));
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
    if (!ThreadManager::wait())
    {
        fprintf(stderr, "Error --> ThreadManager::wait\n");
        return false;
    }
    fprintf(stderr, "Threads terminated successfully\n");

    NetworkManager::closeAll();
    return true;
}