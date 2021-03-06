/* header */
#include <stdio.h>
#include "./sceneManager.h"
#include "./sceneTitle.h"
#include "./sceneLoading.h"
#include "./sceneMainGame.h"
#include "./sceneChara.h"
/* static */
int SceneManager::sceneId;
BaseScene *SceneManager::scenes[SI_NUMBER];

/* method */
bool SceneManager::init(WindowManager *window, ConfigData *config)
{
    sceneId = SI_TITLE;

    scenes[SI_TITLE] = new SceneTitle(window, config);
    scenes[SI_LOADING] = new SceneLoading(window, config);
    scenes[SI_CHARASELECT] = new SceneChara(window, config);
    scenes[SI_MAIN] = new SceneMainGame(window, config);

    for (int i = 0; i < SI_NUMBER; i++)
    {
        if (scenes[i] == NULL)
        {
            fprintf(stderr, "Error --> Scene[%d] is not found\n", i);
            return false;
        }
        if (!scenes[i]->init())
        {
            fprintf(stderr, "Error --> Scene[%d]->init()\n", i);
            return false;
        }
    }
    return true;
}

bool SceneManager::reactController(ControllerParam param)
{
    bool endFlag = false;
    SCENE_ID nextScene = scenes[sceneId]->reactController(param);
    if (nextScene < 0 || SI_NUMBER <= nextScene)
    {
        endFlag = true;
    }
    else
    {
        sceneId = nextScene;
    }
    return endFlag;
}

bool SceneManager::executeCommand(int command)
{
    bool endFlag = false;
    SCENE_ID nextScene = scenes[sceneId]->executeCommand(command);
    if (nextScene < 0 || SI_NUMBER <= nextScene)
    {
        endFlag = true;
    }
    else
    {
        sceneId = nextScene;
    }
    return endFlag;
}

void SceneManager::drawWindow()
{
    scenes[sceneId]->drawWindow();
}