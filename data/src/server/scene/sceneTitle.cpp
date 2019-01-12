#include "./sceneTitle.h"
#include "../../common/network/networkCommand.h"
#include "../../common/network/dataBlock/dataBlock.h"
#include "../network/networkManager.h"
#include "../../common/controllerParam/controllerParam.h"
#include <stdio.h>
bool SceneTitle::init()
{
    return true;
}
SCENE_ID SceneTitle::executeCommand(int command, int pos)
{
    return SI_TITLE;
}
