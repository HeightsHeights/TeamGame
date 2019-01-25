#include "./sceneChara.h"
#include "../../common/network/networkCommand.h"
#include "../../common/network/dataBlock/dataBlock.h"
#include "../../common/controllerParam/controllerParam.h"
#include <stdio.h>

Client SceneChara::player[MAX_CLIENTS];

bool SceneChara::init()
{
    for(int i = 0; i < MAX_PLAYER; i++){
        button[i] = false;
        ready[i] = false;
    }
    return true;
}
SCENE_ID SceneChara::executeCommand(int command, int pos)
{
    if (command == NC_READY)
    {
        DataBlock data;
        data.setCommand2DataBlock(NC_SERVER_MAINGAME);
        NetworkManager::sendData(ALL_CLIENTS, data, data.getDataSize());
        return SI_MAIN;
    }
    else if (command == NC_CONNECT)
    {
        DataBlock data;
        data.setCommand2DataBlock(NC_SERVER_2_CLIENT);
        data.setData(&pos, sizeof(int));
        data.setData(&player[pos].name, sizeof(char *));
        NetworkManager::sendData(ALL_CLIENTS, data, data.getDataSize());
    }
    else if (command == NC_FINISH)
    {
        DataBlock data;
        data.setCommand2DataBlock(NC_FINISH);
        NetworkManager::sendData(ALL_CLIENTS, data, data.getDataSize());
    }
    else if (command == NC_START)
    {
        NetworkManager::recvData(pos, &player[pos].name, sizeof(char *));
        DataBlock data;
        data.setCommand2DataBlock(NC_SERVER_CHARASELSECT);
        NetworkManager::sendData(pos, data, data.getDataSize());
    }
    
    if (command == NC_CONTROLLER_INFO)
    {
        ControllerParam paramData;
        NetworkManager::recvData(pos, &paramData, sizeof(ControllerParam));

        if(button[pos] == true){
            position.x = paramData.axisL.x;
            button[pos] = false;
        }
        else{
            position = Vector2f_ZERO;
        } 

        if(paramData.axisL.x == 0){
            button[pos] = true;
        }
        

        DataBlock data;

        data.setCommand2DataBlock(NC_CONTROLLER_INFO);
        data.setData(&pos, sizeof(int));
        data.setData(position, sizeof(Vector2f));
        NetworkManager::sendData(ALL_CLIENTS, data, data.getDataSize());
    }
    return SI_CHARASELECT;
}