#include "./sceneChara.h"
#include "../../common/network/networkCommand.h"
#include "../../common/network/dataBlock/dataBlock.h"
#include "../network/networkManager.h"
#include "../../common/controllerParam/controllerParam.h"
#include <stdio.h>
bool SceneChara::init()
{
    return true;
}
SCENE_ID SceneChara::executeCommand(int command, int pos)
{
    return SI_CHARA;
}