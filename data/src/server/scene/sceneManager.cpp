/* header */
#include <stdio.h>
#include "./sceneManager.h"
#include "./sceneTitle.h"
#include "./sceneMainGame.h"
#include "./sceneRule.h"
#include "./sceneTeam.h"
#include "./sceneChara.h"
/* static */
int SceneManager::sceneId;
BaseScene *SceneManager::scenes[SI_NUMBER];

/* method */
bool SceneManager::init()
{
    sceneId = 0;

    scenes[SI_TITLE] = new SceneTitle();
    scenes[SI_MAIN] = new SceneMainGame();
    scenes[SI_RULE] = new SceneRule();
    scenes[SI_TEAM] = new SceneTeam();
    scenes[SI_CHARA] = new SceneChara();

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