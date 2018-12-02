#include "./gameSystem.h"

#include "../render/shader/shaderManager.h"
#include "../controller/controllerManager.h"
#include "../scene/sceneManager.h"
#include "../config/loader/configLoader.h"
#include "../config/saver/configSaver.h"
#include "../../common/console/console.h"

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

    if (!loadConfig("cConfig"))
    {
        fprintf(stderr, "Error --> loadConfig()\n");
        return false;
    }

    if (!makeWindow(argc, argv, config->name + "'sGame"))
    {
        fprintf(stderr, "Error --> makeWindow()\n");
        return false;
    }

    if (!ShaderManager::init())
    {
        fprintf(stderr, "Error --> ShaderManager::init()\n");
        return false;
    }
    if (!SceneManager::init(window))
    {
        fprintf(stderr, "Error --> SceneManager::init()\n");
        return false;
    }

    if (!ControllerManager::init())
    {
        fprintf(stderr, "Error --> ControllerManager::init()\n");
        return false;
    }
    return true;
}

bool GameSystem::gameLoop()
{
    while (SDL_AtomicGet(&atm) > 0)
    {

        if (ControllerManager::updateController())
        {
            SDL_AtomicDecRef(&atm);
            break;
        }

        SceneManager::drawWindow();
        SDL_Delay(1);
    }
    return true;
}

bool GameSystem::terminate()
{
    if (!saveConfig("cConfig"))
    {
        fprintf(stderr, "Error --> saveConfig()\n");
        return false;
    }
    return true;
}