#include "./sceneChara.h"
#include "../../common/network/networkCommand.h"
#include "../../common/network/dataBlock/dataBlock.h"
#include "../network/networkManager.h"
#include <stdio.h>
bool SceneChara::init()
{
    return true;
}
SCENE_ID SceneChara::executeCommand(int command, int pos)
{
    if (command == NC_NEXT)
    {
        for (int i = 0; i < 2; i++)
        {
            if (pos == i)
                decision[i] = true;
            else
                decision[i] = false;
        }

        DataBlock data;
        data.setCommand2DataBlock(NC_SERVER_2_CLIENT);
        data.setData(&decision[0], sizeof(bool));
        data.setData(&decision[1], sizeof(bool));
        NetworkManager::sendData(ALL_CLIENTS, data, data.getDataSize());
    }
    return SI_CHARA;
}