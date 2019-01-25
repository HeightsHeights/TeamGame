#include "./sceneChara.h"
#include "../../common/network/networkCommand.h"
#include "../../common/network/dataBlock/dataBlock.h"
#include "../../common/controllerParam/controllerParam.h"
#include <stdio.h>

Player SceneChara::pl[MAX_CLIENTS];

bool SceneChara::init()
{
    for (int i = 0; i < MAX_CLIENTS; i++)
    {
        button[i] = false;
    }
    return true;
}
SCENE_ID SceneChara::executeCommand(int command, int pos)
{
    // if (command == NC_READY)
    // {
    //     for (int i = 0; i < MAX_CLIENTS; i++)
    //     {
    //         gameData[i].tid = (pl[i].position.x == 0) ? TEAM_MUSH : TEAM_BAMBOO;
    //     }

<<<<<<< HEAD
<<<<<<< HEAD
        DataBlock data;
        data.setCommand2DataBlock(NC_SERVER_MAINGAME);
        NetworkManager::sendData(ALL_CLIENTS, data, data.getDataSize());
        return SI_MAIN;
    }
    else if (command == NC_CONNECT)
    {
        NetworkManager::recvData(pos, &gameData[pos].name, sizeof(char *));
        DataBlock data;
        data.setCommand2DataBlock(NC_SERVER_2_CLIENT);
        data.setData(&pos, sizeof(int));
        data.setData(&gameData[pos].name, sizeof(char *));
        NetworkManager::sendData(ALL_CLIENTS, data, data.getDataSize());
    }
    else if (command == NC_FINISH)
    {
        DataBlock data;
        data.setCommand2DataBlock(NC_FINISH);
        NetworkManager::sendData(ALL_CLIENTS, data, data.getDataSize());
    }
=======
=======
>>>>>>> 221e370b01f7ab71cd9a8ba40827cb70d3e27222
    //     DataBlock data;
    //     data.setCommand2DataBlock(NC_SERVER_MAINGAME);
    //     NetworkManager::sendData(ALL_CLIENTS, data, data.getDataSize());
    //     return SI_MAIN;
    // }
    // else if (command == NC_CONNECT)
    // {
    //     DataBlock data;
    //     data.setCommand2DataBlock(NC_SERVER_2_CLIENT);
    //     data.setData(&pos, sizeof(int));
    //     data.setData(&gameData[pos].name, sizeof(char *));
    //     NetworkManager::sendData(ALL_CLIENTS, data, data.getDataSize());
    // }
    // else if (command == NC_FINISH)
    // {
    //     DataBlock data;
    //     data.setCommand2DataBlock(NC_FINISH);
    //     NetworkManager::sendData(ALL_CLIENTS, data, data.getDataSize());
    // }
<<<<<<< HEAD
>>>>>>> 221e370b01f7ab71cd9a8ba40827cb70d3e27222
=======
>>>>>>> 221e370b01f7ab71cd9a8ba40827cb70d3e27222

    // if (command == NC_CONTROLLER_INFO)
    // {
    //     ControllerParam paramData;
    //     NetworkManager::recvData(pos, &paramData, sizeof(ControllerParam));

    //     if (button[pos] == true)
    //     {
    //         pl[pos].position.x += paramData.axisL.x;
    //         button[pos] = false;
    //     }

    //     if (paramData.axisL.x == 0)
    //     {
    //         button[pos] = true;
    //     }

    //     if (pl[pos].position.x > 1)
    //     {
    //         pl[pos].position.x = 0;
    //     }
    //     else if (pl[pos].position.x < 0)
    //     {
    //         pl[pos].position.x = 1;
    //     }

    //     DataBlock data;

    //     data.setCommand2DataBlock(NC_CONTROLLER_INFO);
    //     data.setData(&pos, sizeof(int));
    //     data.setData(pl[pos].position, sizeof(Vector2f));
    //     NetworkManager::sendData(ALL_CLIENTS, data, data.getDataSize());
    // }
    return SI_CHARASELECT;
}