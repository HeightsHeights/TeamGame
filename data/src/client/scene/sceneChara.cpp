#include "./sceneChara.h"
#include "../render/shader/shaderManager.h"
#include "../../common/network/networkCommand.h"
#include "../../common/network/dataBlock/dataBlock.h"
#include "../network/networkManager.h"
#include "../config/loader/configLoader.h"
#include "../audio/audioManager.h"
#define PNG_DIR_PATH "./data/res/gui/image/"

Player SceneChara::player[MAX_PLAYERS];
static const SDL_Color black = {0, 0, 0, 0};

SceneChara::SceneChara(WindowManager *window) : BaseScene(window)
{
}
SceneChara::SceneChara(WindowManager *window, ConfigData *config) : BaseScene(window, config)
{
}
bool SceneChara::init()
{
    isFirst = true;
    angle = 0;
    count = 0;
    secount = 0;
    mush = ObjModelLoader().load("./data/res/gui/obj/kinokochara/", "kinokochara");
    bamboo = ObjModelLoader().load("./data/res/gui/obj/bambooshootchara/", "bambooshootchara");
    const std::string IMAGE_NAME[IMAGE_NUMBER] =
        {
            "configbg.png",
            "charaselsect/mushroom.png",
            "charaselsect/bambooshoot.png",
            "charaselsect/ready.png",
            "charaselsect/namebox1.png",
            "charaselsect/namebox2.png",
            "nameFrames/nameFramenot.png",
        };

    dst[IMAGE_MUSHROOM] = GuiRect(-550, -125, 350, 75);
    dst[IMAGE_READY] = GuiRect(-150, -225, 300, 100);

    for (int i = 0; i < IMAGE_NUMBER; i++)
    {
        image[i] = GuiImageLoader().load((PNG_DIR_PATH + IMAGE_NAME[i]).c_str());
        if (image[i] == NULL)
        {
            return false;
        }
    }

    for (int i = 0; i < MAX_PLAYERS; i++)
    {
        connect[i] = false;
    }

    return true;
}
SCENE_ID SceneChara::reactController(ControllerParam param)
{
    if (isFirst)
    {
        for (int i = 0; i < MAX_PLAYERS; i++)
        {
            SceneChara::player[i].name = &BaseScene::players[i].name[0];
            connect[i] = true;
            isFirst = false;
        }
    }
    if (button == true)
    {
        if (mypos.y == 0)
        {
            mypos.x += param.axisL.x;
        }

        if (count == MAX_PLAYERS / 2)
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

    if (secount > mypos.x || secount < mypos.x)
    {
        secount = mypos.x;
        AudioManager::playSE(SE_CURSOR);
    }

    if (mypos.y == 1 && param.buttonDown[CT_DECITION_OR_ATTACK] && !param.buttonState[CT_DECITION_OR_ATTACK])
    {
        AudioManager::playSE(SE_DECISION);
        DataBlock data;
        data.setCommand2DataBlock(NC_MOVE_SCENE);
        NetworkManager::sendData(data, data.getDataSize());
    }
    else if (param.buttonDown[CT_FINISH])
    {
        DataBlock data;
        data.setCommand2DataBlock(NC_FINISH);
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
    SCENE_ID nextScene = SI_CHARASELECT;
    if (command == NC_MOVE_SCENE)
    {
        AudioManager::fadeOutBGM(BGM_TITLE_OR_SELECT, 3000);
        AudioManager::fadeInBGM(BGM_MAIN, 3000);
        nextScene = SI_MAIN;
    }
    else if (command == NC_FINISH)
    {
        nextScene = SI_NUMBER;
    }
    else if (command == NC_SEND_CONTROLLER_PARAM)
    {
        int num;
        NetworkManager::recvData(&num, sizeof(int));
        Vector2f positionData;

        NetworkManager::recvData(positionData, sizeof(Vector2f));
        player[num].position.x = positionData.x;
    }

    count = 0;
    for (int i = 0; i < MAX_PLAYERS; i++)
    {
        if (player[i].position.x == 0)
        {
            count++;
        }
    }

    return nextScene;
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

    ShaderManager::startShader(SID_NT_PHONG);
    glPushMatrix();
    glScalef(1.0f, 2.0f, 1.0f);
    glTranslatef(-10, -1, positionChara.y);
    glRotated(angle, 0, 1, 0);
    if (mypos.x == 0)
    {
        mush->draw();
    }
    else
    {
        bamboo->draw();
    }
    glPopMatrix();
    ShaderManager::stopShader(SID_NT_PHONG);
}
void SceneChara::draw2D()
{
    float bright;
    if (count == MAX_PLAYERS / 2)
    {
        bright = (mypos.y == 1) ? 1.0f : 0.7f;
    }
    else
    {
        bright = 0.3f;
    }

    ShaderManager::startShader(SID_GUI);
    image[IMAGE_READY]->draw(NULL, &dst[IMAGE_READY], bright);
    image[(int)IMAGE_MUSHROOM + (int)mypos.x]->draw(NULL, &dst[IMAGE_MUSHROOM], (mypos.y == 0) ? 1.0f : 0.3f);
    for (int i = 0; i < MAX_PLAYERS; i++)
    {
        drawPlayer(Vector2f(100, 400 - 120 * i), (player[i].position.x == 0) ? COLOR_RED : COLOR_BLUE, connect[i], player[i].name);
    }
    ShaderManager::stopShader(SID_GUI);
}

void SceneChara::drawPlayer(Vector2f pos, COLOR_ID cid, bool exist, const char *name)
{
    if (!exist)
    {
        GuiRect dst2 = GuiRect(pos.x, pos.y, FRAME_WIDTH, FRAME_WIDTH);
        dst2 = GuiRect(pos.x, pos.y - FRAME_WIDTH * 9 / 8, 6 * FRAME_WIDTH, 100);
        image[IMAGE_NOTPLAYER_FRAME]->draw(NULL, &dst2, 0.5f);
    }
    else
    {
        const Vector2f labelSize = Vector2f(480.0f, 60.0f);
        const float unitWord[1] = {
            20.0f,
        };

        GuiRect dst2 = GuiRect(pos.x, pos.y, FRAME_WIDTH, FRAME_WIDTH);
        dst2 = GuiRect(pos.x, pos.y - FRAME_WIDTH * 9 / 8, 6 * FRAME_WIDTH, 100);
        image[IMAGE_PLAYER_FRAME_0 + cid]->draw(NULL, &dst2, 1.0f);

        float center = pos.x + labelSize.x / 2;
        GuiText *nameText = GuiTextLoader().load(FID_NORMAL, name, black);
        dst2 = GuiRect(center - std::string(name).length() * unitWord[0] / 2, pos.y - 135.0f, std::string(name).length() * unitWord[0], 45.0f);
        nameText->draw(NULL, &dst2, 1.0f);
        delete nameText;
    }
}