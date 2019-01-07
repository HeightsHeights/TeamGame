#include "./sceneTitle.h"
#include "../render/shader/shaderManager.h"
#include "../../common/network/networkCommand.h"
#include "../../common/network/dataBlock/dataBlock.h"
#include "../network/networkManager.h"
#include "../../common/math/quat/quat.h"
#include "../../common/math/angle/angle.h"
#include "../../common/math/matrix/matrixSet.h"
#include "../../common/console/console.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

static const SDL_Color gRed = {0, 0, 255, 0};
SceneTitle::SceneTitle(WindowManager *window) : BaseScene(window)
{
}
SceneTitle::SceneTitle(WindowManager *window, ConfigData *config) : BaseScene(window, config)
{
}
bool SceneTitle::init()
{
    configmode = false;
    image[0] = GuiImageLoader().load("./data/res/gui/image/title.png");
    image[1] = GuiImageLoader().load("./data/res/gui/image/google.png");
    text[0] = GuiTextLoader().load(FID_NORMAL, "NAME", gRed);
    text[1] = GuiTextLoader().load(FID_NORMAL, "ServerID", gRed);
    text[2] = GuiTextLoader().load(FID_NORMAL, "WiimoteID", gRed);
    text[3] = GuiTextLoader().load(FID_NORMAL, config->name.c_str(), gRed);
    text[4] = GuiTextLoader().load(FID_NORMAL, config->serverAddress.c_str(), gRed);
    text[5] = GuiTextLoader().load(FID_NORMAL, config->wiiRemoteId.c_str(), gRed);
    text[6] = GuiTextLoader().load(FID_NORMAL, "Save", gRed);
    text[7] = GuiTextLoader().load(FID_NORMAL, "Cancel", gRed);
    text[8] = GuiTextLoader().load(FID_NORMAL, "Init", gRed);

    for (int i = 0; i < 2; i++)
    {
        if (image[i] == NULL)
        {
            return false;
        }
    }
    for (int i = 0; i < 9; i++)
    {
        if (text[i] == NULL)
        {
            return false;
        }
    }
    return true;
}
SCENE_ID SceneTitle::reactController(ControllerParam param)
{
    if(configmode)
        num = 1;
    else
        num = 0;

    
    if (button == true)
    {
        position[num].x += param.axisL.x;
        position[num].y += param.axisL.y;
        button = false;
    }
    if (param.axisL.x == 0 && param.axisR.y == 0)
    {
        button = true;
    }

    if (position[num].x >= 3)
    {
        position[num].x = 0;
    }
    else if (position[num].x <= -1)
    {
        position[num].x = 1;
    }

    if(position[1].y >= 4){
        position[1].y = 3; 
    }
    else if(position[1].y <= -1){
        position[1].y = 0;
    }

    if(position[1].y != 3){
        position[1].x = 0;
    }

    if(configmode){
        
        if(position[1].y == 0 && param.buttonDown[CT_DECITION_OR_ATTACK] && !param.buttonState[CT_DECITION_OR_ATTACK]){
            Console().scanString("YourName", config->name.c_str(), &config->name);
        }
        else if(position[1].y == 1 && param.buttonDown[CT_DECITION_OR_ATTACK]){
            Console().scanString("ServerAddress", config->serverAddress.c_str(), &config->serverAddress);
        }
    }

    if (position[0].x == 1 && param.buttonDown[CT_DECITION_OR_ATTACK])
    {
        configmode = true;
    }
    else if (position[0].x == 2 && param.buttonDown[CT_DECITION_OR_ATTACK])
    {
        return SI_NUMBER;
    }
    return SI_TITLE;
}
SCENE_ID SceneTitle::executeCommand(int command)
{
    return SI_TITLE;
}
void SceneTitle::draw3D()
{
}
static int i;
void SceneTitle::draw2D()
{

    ShaderManager::startShader(SID_GUI);

    if (configmode)
    {
        i++;
        glPushMatrix();
        glScaled(i, i, 0);
        if (i > 5)
            i = 5;
        text[0]->draw();
        image[1]->draw();
        glPopMatrix();
    }
    else
    {
        i = 0;
        image[0]->draw();
    }
    ShaderManager::stopShader(SID_GUI);
    //名前変更
    // Console().scanString("YourName", config->name.c_str(), &config->name);
    // Console().scanString("ServerAddress", config->serverAddress.c_str(), &config->serverAddress);

    // ShaderManager::startShader(SID_GUI);
    // glBindVertexArray(vao1);
    // glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (void *)0);
    // glBindVertexArray(0);
    // ShaderManager::stopShader(SID_GUI);
}