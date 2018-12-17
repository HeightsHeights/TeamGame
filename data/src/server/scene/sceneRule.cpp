#include "./sceneRule.h"

bool SceneRule::init()
{
    return true;
}
SCENE_ID SceneRule::executeCommand(int command, int pos)
{
    return SI_RULE;
}