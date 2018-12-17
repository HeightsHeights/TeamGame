#include "./sceneTeam.h"

bool SceneTeam::init()
{
    return true;
}
SCENE_ID SceneTeam::executeCommand(int command, int pos)
{
    return SI_TEAM;
}