/* header */
#include <stdio.h>
#include "./sceneManager.h"
#include "./sceneTitle.h"
#include "./sceneMainGame.h"

/* static */
int SceneManager::sceneId;
BaseScene *SceneManager::scenes[SI_NUMBER];

/* method */
bool SceneManager::init(WindowManager *window)
{
    sceneId = 0;

    scenes[SI_TITLE] = new SceneTitle(window);
    scenes[SI_MAIN] = new SceneMainGame(window);

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
    sceneId = scenes[sceneId]->reactController(param);
    if (sceneId < 0 || SI_NUMBER <= sceneId)
    {
        endFlag = true;
    }
    return endFlag;
}

bool SceneManager::executeCommand(int command)
{
    bool endFlag = false;
    sceneId = scenes[sceneId]->executeCommand(command);
    if (sceneId < 0 || SI_NUMBER <= sceneId)
    {
        endFlag = true;
    }
    return endFlag;
}

void SceneManager::drawWindow()
{
    scenes[sceneId]->drawWindow();
}