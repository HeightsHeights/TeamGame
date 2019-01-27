#include "./sceneMainGame.h"

bool SceneMainGame::init()
{
    return true;
}
SCENE_ID SceneMainGame::executeCommand(int command, int pos)
{
    if (command == NC_SEND_CONTROLLER_PARAM)
    {
    }

    return SI_MAIN;
}