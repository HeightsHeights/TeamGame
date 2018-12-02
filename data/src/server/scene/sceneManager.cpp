/* header */
#include <stdio.h>
#include "./sceneManager.h"
#include "./sceneTitle.h"
#include "./sceneMainGame.h"

/* static */
int SceneManager::sceneId;
BaseScene *SceneManager::scenes[SI_NUMBER];

/* method */
bool SceneManager::init()
{
    sceneId = 0;

    scenes[SI_TITLE] = new SceneTitle();
    scenes[SI_MAIN] = new SceneMainGame();

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

bool SceneManager::executeCommand(char command, int pos)
{
    scenes[sceneId]->executeCommand(command, pos);
}