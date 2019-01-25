/* header */
#include <stdio.h>
#include "./sceneManager.h"
#include "./sceneLoading.h"
#include "./sceneMainGame.h"
#include "./sceneChara.h"
/* static */
int SceneManager::sceneId;
BaseScene *SceneManager::scenes[SI_NUMBER];

/* method */
bool SceneManager::init()
{
    sceneId = SI_LOADING;

    scenes[SI_LOADING] = new SceneLoading();
    scenes[SI_MAIN] = new SceneMainGame();
    scenes[SI_CHARASELECT] = new SceneChara();

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

bool SceneManager::executeCommand(int command, int pos)
{
    bool endFlag = false;
    sceneId = scenes[sceneId]->executeCommand(command, pos);
    if (sceneId < 0 || SI_NUMBER <= sceneId)
    {
        endFlag = true;
    }
    return endFlag;
}