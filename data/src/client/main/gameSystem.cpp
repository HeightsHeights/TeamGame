#include "./gameSystem.h"

#include "./threadManager.h"
#include "../render/shader/shaderManager.h"
#include "../render/gui/text/guiTextLoader.h"
#include "../controller/controllerManager.h"
#include "../scene/sceneManager.h"
#include "../config/loader/configLoader.h"
#include "../config/saver/configSaver.h"
#include "../../common/console/console.h"
#include "../network/networkManager.h"
#include "../audio/audioManager.h"

bool GameSystem::loadConfig(std::string fileName)
{
    config = ConfigLoader().load(fileName.c_str());
    if (config == NULL)
    {
        fprintf(stderr, "Error --> ConfigLoader().load()\n");
        return false;
    }
    return true;
}

bool GameSystem::saveConfig(std::string fileName)
{
    if (!ConfigSaver().save(fileName.c_str(), config))
    {
        fprintf(stderr, "Error --> ConfigSave().save()\n");
        return false;
    }
    return true;
}

bool GameSystem::makeWindow(int argc, char *argv[], std::string windowName)
{
    window = new WindowManager(argc, argv, windowName.c_str());
    if (window == NULL)
    {
        return false;
    }
    return true;
}

bool GameSystem::init(int argc, char *argv[])
{
    SDL_AtomicSet(&atm, 1);

    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER | SDL_INIT_AUDIO | SDL_INIT_JOYSTICK))
    {
        fprintf(stderr, "Error --> SDL_Init()\n");
        return false;
    }

    if (!loadConfig("cDefaultConfig"))
    {
        fprintf(stderr, "Error --> loadConfig()\n");
        return false;
    }

    if (!makeWindow(argc, argv, "SuperSmashHogeHoge"))
    {
        fprintf(stderr, "Error --> makeWindow()\n");
        return false;
    }
    if (!ShaderManager::init())
    {
        fprintf(stderr, "Error --> ShaderManager::init()\n");
        return false;
    }
    if (!GuiTextLoader::init())
    {
        fprintf(stderr, "Error --> GuiTextLoader::init()\n");
        return false;
    }

    if (!AudioManager::init())
    {
        fprintf(stderr, "Error --> AudioManager::init()\n");
        return false;
    }

    if (!SceneManager::init(window, config))
    {
        fprintf(stderr, "Error --> SceneManager::init()\n");
        return false;
    }

    if (!ControllerManager::init())
    {
        fprintf(stderr, "Error --> ControllerManager::init()\n");
        return false;
    }

    if (!ThreadManager::init(&atm))
    {
        fprintf(stderr, "Error --> ThreadManager::init()\n");
        return false;
    }
    if (!ThreadManager::start(ThreadManager::controllerThread, "controllerThread"))
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
        SceneManager::drawWindow();
        SDL_Delay(5);
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

#ifndef _UNENABLE_NETWORK
    NetworkManager::disconnect();
#endif
    ControllerManager::cleanUp();

    return true;
}