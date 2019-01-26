#include "./sceneChara.h"
#include "../render/shader/shaderManager.h"
#include "../../common/network/networkCommand.h"
#include "../../common/network/dataBlock/dataBlock.h"
#include "../network/networkManager.h"
#include "../config/loader/configLoader.h"
#include "../audio/audioManager.h"
#define PNG_DIR_PATH "./data/res/gui/image/"

Player SceneChara::player[MAX_PLAYER];
static const SDL_Color black = {0, 0, 0, 0};

SceneChara::SceneChara(WindowManager *window) : BaseScene(window)
{
}
SceneChara::SceneChara(WindowManager *window, ConfigData *config) : BaseScene(window, config)
{
}
bool SceneChara::init()
{
    angle = 0;
    count = 0;
    secount = 0;
    mush = ObjModelLoader().load("./data/res/gui/obj/kinokochara/", "kinokochara");
    bamboo = ObjModelLoader().load("./data/res/gui/obj/bambooshootchara/", "bambooshootchara");
    const std::string IMAGE_NAME[IMAGE_NUMBER] =
        {
            "configbg.png",
            "charaselsect/bambooshoot.png",
            "charaselsect/mushroom.png",
            "ready.png",
            "nameFrames/nameFrameRed.png",
            "nameFrames/nameFrameBlue.png",
            "nameFrames/nameFrameYellow.png",
            "nameFrames/nameFrameGreen.png",
            "nameFrames/nameFramenot.png",
        };

    dst[IMAGE_BAMBOO] = GuiRect(-475, -150, 200, 50);
    dst[IMAGE_READY] = GuiRect(-150, -225, 300, 100);

    for (int i = 0; i < IMAGE_NUMBER; i++)
    {
        image[i] = GuiImageLoader().load((PNG_DIR_PATH + IMAGE_NAME[i]).c_str());
        if (image[i] == NULL)
        {
            return false;
        }
    }

    for (int i = 0; i < COLOR_NUMBER; i++)
    {
        connect[i] = false;
    }

    return true;
}
SCENE_ID SceneChara::reactController(ControllerParam param)
{
    if (button == true)
    {
        if (mypos.y == 0)
        {
            mypos.x += param.axisL.x;
        }

        if (count == MAX_PLAYER / 2)
        {
            mypos.y += param.axisL.y;
        }
        else
        {
            mypos.y = 0;
        }

        button = false;
    }
    if (param.axisL.x == 0 && param.axisL.y == 0)
    {
        button = true;
    }

    if (mypos.x > 1)
    {
        mypos.x = 0;
    }
    else if (mypos.x < 0)
    {
        mypos.x = 1;
    }

    if (mypos.y > 1)
    {
        mypos.y = 1;
    }
    else if (mypos.y < 0)
    {
        mypos.y = 0;
    }

    // if (secount > mypos.x || secount < mypos[0].x)
    // {
    //     secount = mypos.x;
    //     AudioManager::playSE(SE_CURSOR);
    // }

    if (mypos.y == 1 && param.buttonDown[CT_DECITION_OR_ATTACK] && !param.buttonState[CT_DECITION_OR_ATTACK])
    {
        // AudioManager::playSE(SE_DECISION);
        DataBlock data;
        data.setCommand2DataBlock(NC_MOVE_SCENE);
        NetworkManager::sendData(data, data.getDataSize());
    }
    else if (param.buttonDown[CT_FINISH] && !param.buttonState[CT_FINISH])
    {
        DataBlock data;
        data.setCommand2DataBlock(NC_FINISH);
        NetworkManager::sendData(data, data.getDataSize());
    }
    else
    {
        DataBlock data;
        data.setCommand2DataBlock(NC_SEND_CHARA_DATA);
        NetworkManager::sendData(data, data.getDataSize());
    }

    if (mypos.y == 0)
    {
        DataBlock data;
        data.setCommand2DataBlock(NC_SEND_CONTROLLER_PARAM);
        data.setData(&param, sizeof(ControllerParam));
        NetworkManager::sendData(data, data.getDataSize());
    }

    return SI_CHARASELECT;
}
SCENE_ID SceneChara::executeCommand(int command)
{

    if (command == NC_MOVE_SCENE)
    {
        return SI_MAIN;
    }
    else if (command == NC_FINISH)
    {
        return SI_NUMBER;
    }
    else if (command == NC_SEND_CONTROLLER_PARAM)
    {
        int num;
        NetworkManager::recvData(&num, sizeof(int));
        Vector2f positionData;

        NetworkManager::recvData(positionData, sizeof(Vector2f));
        player[num].position.x = positionData.x;
    }
    else if (command == NC_SEND_NAME)
    {
        int num;
        NetworkManager::recvData(&num, sizeof(int));
        connect[num] = true;
        NetworkManager::recvData(&player[num].subname, sizeof(char *));
        player[num].name = &player[num].subname[0];
    }

    count = 0;
    for (int i = 0; i < MAX_PLAYER; i++)
    {
        if (player[i].position.x == 0)
        {
            count++;
        }
    }
    return SI_CHARASELECT;
}

void SceneChara::drawBackground()
{
    ShaderManager::startShader(SID_GUI);
    image[IMAGE_CONFIGBG]->draw(NULL, NULL, 1);
    ShaderManager::stopShader(SID_GUI);
}

void SceneChara::draw3D()
{
    ++angle %= 360;

    gluPerspective(60, WINDOW_WIDTH / WINDOW_HEIGHT, 1.0, 200);
    gluLookAt(-5, 4, 30 + positionChara.y, positionChara.x, 0, positionChara.y, 0, 1, 0);
    float lightPos[] = {-100, 50, 150, 1};
    glLightfv(GL_LIGHT0, GL_POSITION, lightPos);
    glPushMatrix();
    glScalef(1.0f, 2.0f, 1.0f);

    ShaderManager::startShader(SID_NT_PHONG);
    glTranslatef(-10, -1, positionChara.y);
    glRotated(angle, 0, 1, 0);
    if (mypos.x == 0)
    {
        bamboo->draw();
    }
    else
    {
        mush->draw();
    }
    glPopMatrix();
}
void SceneChara::draw2D()
{
    float bright;
    if (count == MAX_PLAYER / 2)
    {
        bright = (mypos.y == 1) ? 1.0f : 0.7f;
    }
    else
    {
        bright = 0.3f;
    }

    ShaderManager::startShader(SID_GUI);
    image[IMAGE_READY]->draw(NULL, &dst[IMAGE_READY], bright);
    image[(int)IMAGE_BAMBOO + (int)mypos.x]->draw(NULL, &dst[IMAGE_BAMBOO], (mypos.y == 0) ? 1.0f : 0.3f);
    for (int i = 0; i < MAX_PLAYER; i++)
    {
        drawPlayer(Vector2f(100, 400 - 120 * i), (player[i].position.x == 0) ? COLOR_RED : COLOR_BLUE, connect[i], player[i].name);
    }
    ShaderManager::stopShader(SID_GUI);
}

void SceneChara::drawPlayer(Vector2f pos, COLOR_ID cid, bool exit, const char *name)
{
    if (!exit)
    {
        GuiRect dst2 = GuiRect(pos.x, pos.y, FRAME_WIDTH, FRAME_WIDTH);
        dst2 = GuiRect(pos.x, pos.y - FRAME_WIDTH * 9 / 8, 6 * FRAME_WIDTH, FRAME_WIDTH);
        image[IMAGE_NOTPLAYER_FRAME]->draw(NULL, &dst2, 0.5f);
    }
    else
    {
        GuiRect dst2 = GuiRect(pos.x, pos.y, FRAME_WIDTH, FRAME_WIDTH);
        dst2 = GuiRect(pos.x, pos.y - FRAME_WIDTH * 9 / 8, 6 * FRAME_WIDTH, FRAME_WIDTH);
        image[IMAGE_PLAYER_FRAME_0 + cid]->draw(NULL, &dst2, 1.0f);

        GuiText *nameText = GuiTextLoader().load(FID_NORMAL, name, black);
        dst2 = GuiRect(pos.x + FRAME_WIDTH * 2 - std::string(name).length() * 15 / 2 + FRAME_WIDTH / 2, pos.y - FRAME_WIDTH * 11 / 9, std::string(name).length() * 30, 60);
        nameText->draw(NULL, &dst2, 1.0f);
        delete nameText;
    }
}