#include "./sceneTitle.h"

bool SceneTitle::init()
{
    return true;
}
SCENE_ID SceneTitle::executeCommand(int command, int pos)
{
    return SI_TITLE;
}
