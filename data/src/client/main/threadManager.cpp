#include "./threadManager.h"
#include "../controller/controllerManager.h"
#include "../scene/sceneManager.h"
#include "../network/networkManager.h"

std::vector<SDL_Thread *> ThreadManager::threads;
void *ThreadManager::data;

bool ThreadManager::init(void *data)
{
    ThreadManager::data = data;
    return true;
}
bool ThreadManager::start(SDL_ThreadFunction fp, const char *name)
{
    SDL_Thread *thread = SDL_CreateThread(fp, name, data);
    if (thread == NULL)
    {
        fprintf(stderr, "Error --> SDL_CreateThread()\n");
        return false;
    }
    threads.push_back(thread);
    return true;
}
int ThreadManager::networkThread(void *data)
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
    return 1;
}
int ThreadManager::controllerThread(void *data)
{
    while (SDL_AtomicGet((SDL_atomic_t *)data) > 0)
    {
        if (ControllerManager::updateController())
        {
            SDL_AtomicDecRef((SDL_atomic_t *)data);
        }
        SDL_Delay(5);
    }
    return 1;
}

bool ThreadManager::wait()
{
    bool ret = true;

    int threadReturnValue;
    for (int i = 0; i < threads.size(); i++)
    {
        SDL_WaitThread(threads[i], &threadReturnValue);
        if (threadReturnValue < 0)
        {
            fprintf(stderr, "Error --> thread[%d] is Abend\n", i);
            ret = false;
        }
    }

    return ret;
}
