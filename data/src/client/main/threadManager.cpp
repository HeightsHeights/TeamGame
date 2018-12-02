#include "./threadManager.h"
#include "../controller/controllerManager.h"
#include "../scene/sceneManager.h"
#include "../network/networkManager.h"

bool ThreadManager::init(void *data)
{
    SDL_Thread *cThread = SDL_CreateThread(controllerThread, "ControllerThread", data);
    if (cThread == NULL)
    {
        fprintf(stderr, "Error --> SDL_CreateThread()\n");
        return false;
    }
#ifndef _UNENABLE_NETWORK
    SDL_Thread *nThread = SDL_CreateThread(netWorkThread, "NetworkThread", data);
    if (nThread == NULL)
    {
        fprintf(stderr, "Error --> SDL_CreateThread()\n");
        return false;
    }
#endif
    return true;
}
int ThreadManager::netWorkThread(void *data)
{
    while (SDL_AtomicGet((SDL_atomic_t *)data) > 0)
    {
        fd_set readOK;
        if (!NetworkManager::waitRequest(&readOK))
        {
            fprintf(stderr, "Error --> NetworkManager::waitRequest()\n");
            return -1;
        }

        int gSocket = NetworkManager::getGSocket();
        if (FD_ISSET(gSocket, &readOK))
        {
            int command;
            NetworkManager::recvData(&command, sizeof(int));
            if (SceneManager::executeCommand(command))
            {
                SDL_AtomicDecRef((SDL_atomic_t *)data);
            }
        }
    }
}
int ThreadManager::controllerThread(void *data)
{
    while (SDL_AtomicGet((SDL_atomic_t *)data) > 0)
    {
        if (ControllerManager::updateController())
        {
            SDL_AtomicDecRef((SDL_atomic_t *)data);
        }
    }
}