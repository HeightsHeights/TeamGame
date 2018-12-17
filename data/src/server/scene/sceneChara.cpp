#include "./sceneChara.h"

bool SceneChara::init()
{
    return true;
}
SCENE_ID SceneChara::executeCommand(int command, int pos)
{
    return SI_CHARA;
}