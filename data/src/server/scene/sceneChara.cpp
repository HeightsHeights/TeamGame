#include "./sceneChara.h"
#include "../../common/network/networkCommand.h"
#include "../../common/network/dataBlock/dataBlock.h"
#include "../network/networkManager.h"
#include <stdio.h>
#include <string.h>
#include <sstream>
bool SceneChara::init()
{
    return true;
}
SCENE_ID SceneChara::executeCommand(int command, int pos)
{
    if (command == NC_READY && ready[pos] == false)
    {
        int count = 0;
        int gClientNum = NetworkManager::getGClientNum();
        ready[pos] = true;

        for (int i = 0; i < gClientNum; i++)
        {
            if (ready[i] == true)
            {
                count++;
            }
        }

        if (count == gClientNum && gClientNum > 1)
        {
            DataBlock data;
            data.setCommand2DataBlock(NC_SERVER_MAINGAME);
            NetworkManager::sendData(ALL_CLIENTS, data, data.getDataSize());
            return SI_MAIN;
        }
        else
        {
            DataBlock data;
            data.setCommand2DataBlock(NC_SERVER_READY);
            data.setData(&pos, sizeof(int));
            NetworkManager::sendData(ALL_CLIENTS, data, data.getDataSize());
        }
    }
    else if (command == NC_CANCEL && ready[pos] == true)
    {
        ready[pos] = false;
        DataBlock data;
        data.setCommand2DataBlock(NC_SERVER_CANCEL);
        data.setData(&pos, sizeof(int));
        NetworkManager::sendData(ALL_CLIENTS, data, data.getDataSize());
    }
    else if(command == NC_CONNECT)
    {
        // std::string cstr;
        // std::ostringstream oss;
        // char name[50];
        // const char *myname;
        // NetworkManager::recvData(pos, &name, sizeof(char *));
        // oss << pos;
        // cstr = std::string(name);
        // myname = (oss.str() + cstr).c_str();
        // strcpy(name,myname);


        DataBlock data;
        data.setCommand2DataBlock(NC_SERVER_2_CLIENT);
        //data.setData(&name, sizeof(char *));
        data.setData(&pos, sizeof(int));
        NetworkManager::sendData(ALL_CLIENTS, data, data.getDataSize());
    }
    else if(command == NC_START){
        DataBlock data;
        data.setCommand2DataBlock(NC_SERVER_CHARASELSECT);
        NetworkManager::sendData(pos, data, data.getDataSize());
    }
    return SI_CHARASELECT;
}