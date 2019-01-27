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
#include "../controller/controllerManager.h"
#include "../main/threadManager.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <fstream>

#define PNG_DIR_PATH "./data/res/gui/image/"
#define PNG_FILE_EXTENSION ".png"

static const SDL_Color gRed = {0, 0, 255, 0};

SceneTitle::SceneTitle(WindowManager *window) : BaseScene(window)
{
}
SceneTitle::SceneTitle(WindowManager *window, ConfigData *config) : BaseScene(window, config)
{
}
bool SceneTitle::init()
{
    const std::string IMAGE_NAME[SceneTitle::IMAGE_NUMBER] =
        {
            "title/title.png",
            "title/back.png",
            "title/start.png",
            "title/config.png",
            "title/end.png",
            "title/save.png",
            "title/cancel.png",
            "title/reset.png",
            "title/connect.png",
            "configFrames/configFrame00.png",
            "configFrames/configFrame01.png",
            "configFrames/configFrame02.png",
        };
    //AudioManager::playBGM(BGM_TITLE);

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

    text[TEXT_SAVE] = GuiTextLoader().load(FID_NORMAL, "Save", gRed);
    text[TEXT_CANCEL] = GuiTextLoader().load(FID_NORMAL, "Cancel", gRed);
    text[TEXT_RESET] = GuiTextLoader().load(FID_NORMAL, "Reset", gRed);

    for (int i = 0; i < TEXT_NUMBER; i++)
    {
        if (text[i] == NULL)
        {
            return false;
        }
    }

    configPos = Vector2f(0, 440);

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

    if (position[0].x > 2 || position[1].x > 3)
    {
        position[num].x = 0;
    }
    else if (position[num].x < 0)
    {
        position[num].x = (num == 0) ? 2 : 3;
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

    // if (secount > position[0].x || secount < position[0].x)
    // {
    //     secount = position[0].x;
    //     AudioManager::playSE(SE_CURSOR);
    // }

    if (configmode)
    {
        if (position[1].y == 0 && param.buttonDown[CT_DECITION_OR_ATTACK] && !param.buttonState[CT_DECITION_OR_ATTACK])
        {
            Console().scanString("YourName", subconfig->name.c_str(), &subconfig->name);
        }
        else if (position[1].y == 1 && param.buttonDown[CT_DECITION_OR_ATTACK] && !param.buttonState[CT_DECITION_OR_ATTACK])
        {
            Console().scanString("ServerAddress", subconfig->serverAddress.c_str(), &subconfig->serverAddress);
        }
        else if (position[1].y == 2 && param.buttonDown[CT_DECITION_OR_ATTACK] && !param.buttonState[CT_DECITION_OR_ATTACK])
        {
            Console().scanString("WiiRemoteId", subconfig->wiiRemoteId.c_str(), &subconfig->wiiRemoteId);
        }

        if (position[1].y == 3 && position[1].x == 0 && param.buttonDown[CT_DECITION_OR_ATTACK] && !param.buttonState[CT_DECITION_OR_ATTACK])
        {
            ConfigSaver().save("cPrevConfig", subconfig);
            config = subconfig;
            configmode = false;
        }
        else if (position[1].y == 3 && position[1].x == 1 && param.buttonDown[CT_DECITION_OR_ATTACK] && !param.buttonState[CT_DECITION_OR_ATTACK])
        {
            configmode = false;
        }
        else if (position[1].y == 3 && position[1].x == 2 && param.buttonDown[CT_DECITION_OR_ATTACK] && !param.buttonState[CT_DECITION_OR_ATTACK])
        {
            subconfig = ConfigLoader().load("cDefaultConfig");
        }
        else if (position[1].y == 3 && position[1].x == 3 && param.buttonDown[CT_DECITION_OR_ATTACK] && !param.buttonState[CT_DECITION_OR_ATTACK])
        {
#ifdef _ENABLE_WII
            if (!ControllerManager::connectWiiRemote(subconfig->wiiRemoteId.c_str()))
            {
                fprintf(stderr, "Error --> ControllerManager::connectWiiRemoteController()\n");
            }
#endif
        }

        if (param.buttonDown[CT_CANCEL] && !param.buttonState[CT_CANCEL])
        {
            configmode = false;
        }
    }
    else
    {
        position[1].x = 0;
        position[1].y = 0;

        if (position[0].x == 0 && param.buttonDown[CT_DECITION_OR_ATTACK] && !param.buttonState[CT_DECITION_OR_ATTACK])
        {
        // AudioManager::playSE(SE_DECISION);
#ifndef _UNENABLE_NETWORK
            if (!NetworkManager::init(config->serverAddress.c_str()))
            {
                fprintf(stderr, "Error --> NetworkManager::init()\n");
            }
            else
            {
                if (!NetworkManager::connect())
                {
                    fprintf(stderr, "Error --> NetworkManager::connect()\n");
                    // AudioManager::playSE(SE_MISS);
                }
                else if (!ThreadManager::start(ThreadManager::networkThread, "networkThread"))
                {
                    fprintf(stderr, "Error --> ThreadManager::start()\n");
                }
                else
                {
                    //AudioManager::stopBGM(BGM_TITLE);
                    return SI_LOADING;
                }
            }
#endif
        }
        else if (position[0].x == 1 && param.buttonDown[CT_DECITION_OR_ATTACK] && !param.buttonState[CT_DECITION_OR_ATTACK])
        {
            // AudioManager::playSE(SE_DECISION);
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
    if (command == NC_MOVE_SCENE)
    {
        return SI_CHARASELECT;
    }
    return SI_TITLE;
}
void SceneTitle::draw3D()
{
}
void SceneTitle::draw2D()
{
    ShaderManager::startShader(SID_GUI);

    image[IMAGE_BG]->draw(NULL, NULL, bright);
    image[IMAGE_TITLE]->draw(NULL, &dst[IMAGE_TITLE], bright);

    image[IMAGE_START + (int)position[0].x]->draw(NULL, &dst[IMAGE_START], bright);

    if (!configmode)
    {
        configPos.x = 640;

        bright += 0.1f;
        if (bright > 1.0f)
        {
            bright = 1.0f;
        }
        image[(int)IMAGE_START + (int)position[0].x]->draw(NULL, &dst[IMAGE_START], bright);
    }
    else
    {
        bright -= 0.1f;
        if (bright < 0.4f)
        {
            bright = 0.4f;
        }
        configPos.x -= 10;
        if (configPos.x <= -200)
        {
            configPos.x = -200;
        }
        drawConfig(configPos);
    }

    ShaderManager::stopShader(SID_GUI);
}

void SceneTitle::drawConfig(Vector2f pos)
{
    dst[IMAGE_CONFIG_FRAME_0] = GuiRect(pos.x - 50, pos.y, 500, 880);
    image[IMAGE_CONFIG_FRAME_0]->draw(NULL, &dst[IMAGE_CONFIG_FRAME_0]);

    drawConfigElement(pos + Vector2f(0, -140), std::string("Name"), subconfig->name, position[1].y == 0);
    drawConfigElement(pos + Vector2f(0, -290), std::string("ServerAddress"), subconfig->serverAddress, position[1].y == 1);
    drawConfigElement(pos + Vector2f(0, -440), std::string("WiimoteID"), subconfig->wiiRemoteId, position[1].y == 2);

    dst[IMAGE_SAVE] = GuiRect(pos.x, -200, 400, 80);
    image[(int)IMAGE_SAVE + (int)position[1].x]->draw(NULL, &dst[IMAGE_SAVE], position[1].y == 3 ? 1.0f : 0.6f);
}
void SceneTitle::drawConfigElement(Vector2f pos, std::string label, std::string string, bool selected)
{

    const Vector2f labelSize = Vector2f(150.0f, 50.0f);
    const Vector2f stringSize = Vector2f(400.0f, 80.0f);

    const float unitWord[2] = {
        10.0f,
        20.0f,
    };

    float brightness = selected ? 1.0f : 0.6f;

    dst[IMAGE_CONFIG_FRAME_1] = GuiRect(pos.x, pos.y, labelSize.x, labelSize.y);
    dst[IMAGE_CONFIG_FRAME_2] = GuiRect(pos.x, pos.y - labelSize.y, stringSize.x, stringSize.y);

    image[IMAGE_CONFIG_FRAME_1]->draw(NULL, &dst[IMAGE_CONFIG_FRAME_1], brightness);
    image[IMAGE_CONFIG_FRAME_2]->draw(NULL, &dst[IMAGE_CONFIG_FRAME_2], brightness);

    float center = pos.x + labelSize.x / 2;
    GuiText *text = GuiTextLoader().load(FID_NORMAL, label.c_str(), gRed);
    GuiRect dst = GuiRect(center - label.length() * unitWord[0] / 2, pos.y - labelSize.y / 4, label.length() * unitWord[0], labelSize.y / 2);
    text->draw(NULL, &dst, brightness);
    delete text;

    center = pos.x + stringSize.x / 2;
    text = GuiTextLoader().load(FID_NORMAL, string.c_str(), gRed);
    dst = GuiRect(center - string.length() * unitWord[1] / 2, pos.y - labelSize.y * 5 / 4, string.length() * unitWord[1], labelSize.y);
    text->draw(NULL, &dst, brightness);
    delete text;
}