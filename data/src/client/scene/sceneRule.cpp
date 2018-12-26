#include "./sceneRule.h"
#include "../../common/network/networkCommand.h"
#include "../../common/network/dataBlock/dataBlock.h"
#include "../network/networkManager.h"
SceneRule::SceneRule(WindowManager *window) : BaseScene(window)
{
}
bool SceneRule::init()
{
    for(int i = 0;i < 2; i++){
        position[i] = Vector2f_ZERO;
    }
    return true;
}
SCENE_ID SceneRule::reactController(ControllerParam param)
{
    if(position[0].y == 2 && position[0].x == 0 && param.buttonDown[CT_DECITION_OR_ATTACK]){
        DataBlock data;
        data.setCommand2DataBlock(NC_SINGLE);
        NetworkManager::sendData(data,data.getDataSize());
    }
    else if(position[0].y == 2 && position[0].x == 1 && param.buttonDown[CT_DECITION_OR_ATTACK]){
        DataBlock data;
        data.setCommand2DataBlock(NC_TEAM);
        NetworkManager::sendData(data,data.getDataSize());
    }
    else{
        DataBlock data;
        data.setCommand2DataBlock(NC_CONTROLLER_INFO);
        data.setData(&param,sizeof(ControllerParam));
        NetworkManager::sendData(data,data.getDataSize());
    }
    
    return SI_RULE;
}
SCENE_ID SceneRule::executeCommand(int command)
{
    if(command == NC_SERVER_2_CLIENT){
        Vector2f positionData;
        NetworkManager::recvData(positionData,sizeof(Vector2f));

        position[0].y += positionData.y;
        
        if(position[0].y == 3){
            position[0].y = 0;
        }
        else if(position[0].y == -1){
            position[0].y = 2;
        }

        if(position[0].y == 0){
            position[0].x += positionData.x;
        }
        else if(position[0].y == 1){
            position[1].x += positionData.x;
        }

        for(int i = 0; i < 2; i++){
            if(position[i].x == 2){
                position[i].x = 0;
            }
            else if(position[i].x == -1){
                position[i].x = 1;
            }
        }
    }
    else if(command == NC_SERVER_CHARASELSECT){
        return SI_CHARASELECT;
    }
    else if(command == NC_SERVER_TEAMSELECT){
        return SI_TEAMSELECT;
    }
    
    return SI_RULE;
}
void SceneRule::draw3D()
{
}
void SceneRule::draw2D()
{
}