#include "./sceneTitle.h"
#include "../render/shader/shaderManager.h"
#include "../../common/network/networkCommand.h"
#include "../../common/network/dataBlock/dataBlock.h"
#include "../network/networkManager.h"
#include "../../common/math/quat/quat.h"
#include "../../common/math/angle/angle.h"
#include "../../common/math/matrix/matrixSet.h"
#include "../../common/console/console.h"
#include "../config/saver/configSaver.h"
#include "../config/loader/configLoader.h"
#include "../audio/audioManager.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <fstream>

#define PNG_DIR_PATH "./data/res/gui/image/"

static const SDL_Color gRed = {0, 0, 255, 0};

std::string IMAGE_NAME[SceneTitle::IMAGE_NUMBER] =
    {
        "title.png",
        "back.png",
        "start.png",
        "config.png",
        "end.png",
        "save.png",
        "cancel.png",
        "reset.png",
};

SceneTitle::SceneTitle(WindowManager *window) : BaseScene(window)
{
}
SceneTitle::SceneTitle(WindowManager *window, ConfigData *config) : BaseScene(window, config)
{
}
bool SceneTitle::init()
{
    config = ConfigLoader().load("cPrevConfig");
    subconfig = config;
    secount = 0;
    dst[IMAGE_START] = GuiRect(-200, -180, 400, 80);
    dst[IMAGE_TITLE] = GuiRect(-393, 256, 786, 255);
    configmode = false;
    for (int i = 0; i < IMAGE_NUMBER; i++)
    {
        image[i] = GuiImageLoader().load((PNG_DIR_PATH + IMAGE_NAME[i]).c_str());
        if (image[i] == NULL)
        {
            return false;
        }
    }

    text[TEXT_YOUSERNAME] = GuiTextLoader().load(FID_NORMAL, config->name.c_str(), gRed);
    text[TEXT_SERVERID] = GuiTextLoader().load(FID_NORMAL, config->serverAddress.c_str(), gRed);
    text[TEXT_WIIMOTEID] = GuiTextLoader().load(FID_NORMAL, subconfig->wiiRemoteId.c_str(), gRed);
    text[TEXT_SAVE] = GuiTextLoader().load(FID_NORMAL, "Save", gRed);
    text[TEXT_CANCEL] = GuiTextLoader().load(FID_NORMAL, "Cancel", gRed);
    text[TEXT_RESET] = GuiTextLoader().load(FID_NORMAL, "Reset", gRed);
    text[TEXT_NAMETITLE] = GuiTextLoader().load(FID_NORMAL, "NAME", gRed);
    text[TEXT_SERVERTITLE] = GuiTextLoader().load(FID_NORMAL, "ServerID", gRed);
    text[TEXT_WIITITLE] = GuiTextLoader().load(FID_NORMAL, "WiimoteID", gRed);

    for (int i = 0; i < TEXT_NUMBER; i++)
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
    if (configmode)
        num = 1;
    else
        num = 0;

    if (button == true)
    {
        position[num].x += param.axisL.x;
        position[num].y += param.axisL.y;
        button = false;
    }
    if (param.axisL.x == 0 && param.axisL.y == 0)
    {
        button = true;
    }

    if (position[num].x > 2)
    {
        position[num].x = 0;
    }
    else if (position[num].x < 0)
    {
        position[num].x = 2;
    }

    if (position[1].y > 3)
    {
        position[1].y = 3;
    }
    else if (position[1].y < 0)
    {
        position[1].y = 0;
    }

    if (position[1].y != 3)
    {
        position[1].x = 0;
    }

    if (secount > position[0].x || secount < position[0].x)
    {
        secount = position[0].x;
        AudioManager::playSE(SE_CURSOR);
    }

    if (configmode)
    {

        if (position[1].y == 0 && param.buttonDown[CT_DECITION_OR_ATTACK] && !param.buttonState[CT_DECITION_OR_ATTACK])
        {
            Console().scanString("YourName", config->name.c_str(), &config->name);
        }
        else if (position[1].y == 1 && param.buttonDown[CT_DECITION_OR_ATTACK] && !param.buttonState[CT_DECITION_OR_ATTACK])
        {
            Console().scanString("ServerAddress", config->serverAddress.c_str(), &config->serverAddress);
        }

        if (position[1].y == 3 && position[1].x == 0 && param.buttonDown[CT_DECITION_OR_ATTACK] && !param.buttonState[CT_DECITION_OR_ATTACK])
        {
            ConfigSaver().save("cPrevConfig", config);
            configmode = false;
        }
        else if (position[1].y == 3 && position[1].x == 1 && param.buttonDown[CT_DECITION_OR_ATTACK] && !param.buttonState[CT_DECITION_OR_ATTACK])
        {
            configmode = false;
        }
        else if (position[1].y == 3 && position[1].x == 2 && param.buttonDown[CT_DECITION_OR_ATTACK])
        {
            subconfig = ConfigLoader().load("cDefaultConfig");
        }
    }
    else
    {
        position[1].x = 0;
        position[1].y = 0;

        if (position[0].x == 0 && param.buttonDown[CT_DECITION_OR_ATTACK] && !param.buttonState[CT_DECITION_OR_ATTACK])
        {
            AudioManager::playSE(SE_DECISION);
            DataBlock data;
            data.setCommand2DataBlock(NC_READY);
            NetworkManager::sendData(data, data.getDataSize());
        }
        else if (position[0].x == 1 && param.buttonDown[CT_DECITION_OR_ATTACK] && !param.buttonState[CT_DECITION_OR_ATTACK])
        {
            AudioManager::playSE(SE_DECISION);
            configmode = true;
        }
        else if (position[0].x == 2 && param.buttonDown[CT_DECITION_OR_ATTACK] && !param.buttonState[CT_DECITION_OR_ATTACK])
        {
            return SI_NUMBER;
        }
    }
    return SI_TITLE;
}
SCENE_ID SceneTitle::executeCommand(int command)
{
    if (command == NC_SERVER_CHARASELSECT)
    {
        return SI_CHARASELECT;
    }
    return SI_TITLE;
}
void SceneTitle::draw3D()
{
}
static int i;
void SceneTitle::draw2D()
{
    ShaderManager::startShader(SID_GUI);

    image[IMAGE_BG]->draw(NULL, NULL, bright);
    image[IMAGE_TITLE]->draw(NULL, &dst[IMAGE_TITLE], bright);

    if (position[0].x == 0)
    {
        image[IMAGE_START]->draw(NULL, &dst[IMAGE_START], bright);
    }
    else if (position[0].x == 1)
    {
        image[IMAGE_CONFIG]->draw(NULL, &dst[IMAGE_START], bright);
    }
    else if (position[0].x == 2)
    {
        image[IMAGE_END]->draw(NULL, &dst[IMAGE_START], bright);
    }

    if (!configmode)
    {
        i = 640;
        bright += 0.1;
        if (bright > 1)
            bright = 1;

        if (position[0].x == 0)
        {
            image[IMAGE_START]->draw(NULL, &dst[IMAGE_START], bright);
        }
        else if (position[0].x == 1)
        {
            image[IMAGE_CONFIG]->draw(NULL, &dst[IMAGE_START], bright);
        }
        else if (position[0].x == 2)
        {
            image[IMAGE_END]->draw(NULL, &dst[IMAGE_START], bright);
        }
    }
    else
    {
        bright -= 0.1;
        if (bright < 0.4)
            bright = 0.4;
        i -= 10;
        if (i <= -200)
            i = -200;
        dst2[TEXT_YOUSERNAME] = GuiRect(i + 10, 250, 350, 80);
        dst2[TEXT_SERVERID] = GuiRect(i + 10, 100, 350, 80);
        dst2[TEXT_WIIMOTEID] = GuiRect(i + 12, -50, 350, 80);
        dst2[TEXT_NAMETITLE] = GuiRect(i, 300, 175, 40);
        dst2[TEXT_SERVERTITLE] = GuiRect(i, 150, 175, 40);
        dst2[TEXT_WIITITLE] = GuiRect(i + 2, 0, 175, 40);
        dst[IMAGE_SAVE] = GuiRect(i, -200, 400, 80);
        if (position[1].x == 0)
        {
            image[IMAGE_SAVE]->draw(NULL, &dst[IMAGE_SAVE]);
        }
        else if (position[1].x == 1)
        {
            image[IMAGE_CANCEL]->draw(NULL, &dst[IMAGE_SAVE]);
        }
        else if (position[1].x == 2)
        {
            image[IMAGE_RESET]->draw(NULL, &dst[IMAGE_SAVE]);
        }

        delete text[TEXT_YOUSERNAME];
        delete text[TEXT_SERVERID];
        text[TEXT_YOUSERNAME] = GuiTextLoader().load(FID_NORMAL, subconfig->name.c_str(), gRed);
        text[TEXT_SERVERID] = GuiTextLoader().load(FID_NORMAL, subconfig->serverAddress.c_str(), gRed);

        for (int i = 3; i < TEXT_NUMBER; i++)
        {
            text[i]->draw(NULL, &dst2[i]);
        }
    }

    ShaderManager::stopShader(SID_GUI);
    // ShaderManager::startShader(SID_GUI);
    // glBindVertexArray(vao1);
    // glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (void *)0);
    // glBindVertexArray(0);
    //ShaderManager::stopShader(SID_GUI);
}