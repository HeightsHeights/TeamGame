#include "./sceneChara.h"
#include "../render/shader/shaderManager.h"
#include "../../common/network/networkCommand.h"
#include "../../common/network/dataBlock/dataBlock.h"
#include "../network/networkManager.h"

#define PNG_DIR_PATH "./data/res/gui/image/"

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
    mush = ObjModelLoader().load("./data/res/gui/obj/kinokochara/", "kinokochara");
    bamboo = ObjModelLoader().load("./data/res/gui/obj/bambooshootchara/", "bambooshootchara");
    std::string IMAGE_NAME[IMAGE_NUMBER] =
        {
            "configbg.png",
            "bamboo.png",
            "mushroom.png",
            "ready.png",
            "nameFrames/nameFrameRed.png",
            "nameFrames/nameFrameBlue.png",
            "nameFrames/nameFrameYellow.png",
            "nameFrames/nameFrameGreen.png",
            "nameFrames/nameFramenot.png",
            "check.png",
        };

    dst[IMAGE_BAMBOO] = GuiRect(-500, -150, 200, 50);
    dst[IMAGE_READY] = GuiRect(-150, -225, 300, 100);
    own = false;
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
        connect[i] = true;
        decision[i] = false;
    }

    return true;
}
SCENE_ID SceneChara::reactController(ControllerParam param)
{
    if (!own && button == true)
    {
        if (position.y == 0)
        {
            position.x += param.axisL.x;
        }
        position.y += param.axisL.y;
        button = false;
    }
    if (param.axisL.x == 0 && param.axisL.y == 0)
    {
        button = true;
    }

    if (position.x > 1)
    {
        position.x = 0;
    }
    else if (position.x < 0)
    {
        position.x = 1;
    }

    if (position.y > 1)
    {
        position.y = 1;
    }
    else if (position.y < 0)
    {
        position.y = 0;
    }

    if (!own && position.y == 1 && param.buttonDown[CT_DECITION_OR_ATTACK] && !param.buttonState[CT_DECITION_OR_ATTACK])
    {
        own = true;
        DataBlock data;
        data.setCommand2DataBlock(NC_READY);
        NetworkManager::sendData(data, data.getDataSize());
    }
    else if (own == true && position.y == 1 && param.buttonDown[CT_CANCEL] && !param.buttonState[CT_CANCEL])
    {
        own = false;
        DataBlock data;
        data.setCommand2DataBlock(NC_CANCEL);
        NetworkManager::sendData(data, data.getDataSize());
    }
    else
    {
        // const char *myname;
        // char name[50];
        // myname = config->name.c_str();
        // strcpy(name,myname);
        DataBlock data;
        data.setCommand2DataBlock(NC_CONNECT);
        //data.setData(&name, sizeof(char *));
        NetworkManager::sendData(data, data.getDataSize());
            
        
    }

    return SI_CHARASELECT;
}
SCENE_ID SceneChara::executeCommand(int command)
{
    if (command == NC_SERVER_READY)
    {
        int num;
        NetworkManager::recvData(&num, sizeof(int));
        decision[num] = true;
    }
    else if (command == NC_SERVER_CANCEL)
    {
        int num;
        NetworkManager::recvData(&num, sizeof(int));
        decision[num] = false;
    }
    else if (command == NC_SERVER_MAINGAME)
    {
        return SI_MAIN;
    }
    else if (command == NC_SERVER_2_CLIENT)
    {
        int num;
        // char name[50];
        /NetworkManager::recvData(&num, sizeof(int));
        connect[num] = true;
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
    gluLookAt(-5, 4, 30 + positionMush.y, positionMush.x, 0, positionMush.y, 0, 1, 0);
    float lightPos[] = {-100, 50, 150, 1};
    glLightfv(GL_LIGHT0, GL_POSITION, lightPos);
    glPushMatrix();
    glScalef(1.0f, 2.0f, 1.0f);

    ShaderManager::startShader(SID_NT_PHONG);
    glTranslatef(-10, -1, positionMush.y);
    glRotated(angle, 0, 1, 0);
    mush->draw();
    glPopMatrix();
}
void SceneChara::draw2D()
{
    ShaderManager::startShader(SID_GUI);
    image[IMAGE_READY]->draw(NULL, &dst[IMAGE_READY], (position.y == 1 && !own) ? 1.0f : 0.3f);
    image[(int)IMAGE_BAMBOO + (int)position.x]->draw(NULL, &dst[IMAGE_BAMBOO], (position.y == 0) ? 1.0f : 0.3f);
    drawPlayer(Vector2f(100, 400), COLOR_RED, connect[0], decision[0], "SYM");
    drawPlayer(Vector2f(100, 280), COLOR_BLUE, connect[1], decision[1], "aaa");
    drawPlayer(Vector2f(100, 160), COLOR_YELLOW, connect[2], decision[2], "sss");
    drawPlayer(Vector2f(100, 40), COLOR_GREEN, connect[3], decision[3], "suyama");
    ShaderManager::stopShader(SID_GUI);
}

void SceneChara::drawPlayer(Vector2f pos, COLOR_ID cid, bool exit, bool ready, const char *name)
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

        dst2 = GuiRect(pos.x - FRAME_WIDTH, pos.y - FRAME_WIDTH * 9 / 8, FRAME_WIDTH, FRAME_WIDTH);
        image[IMAGE_CHECK]->draw(NULL, &dst2, (ready) ? 1.0f : 0.2f);

        GuiText *nameText = GuiTextLoader().load(FID_NORMAL, name, black);
        dst2 = GuiRect(pos.x + FRAME_WIDTH * 2 - std::string(name).length() * 15 / 2 + FRAME_WIDTH / 2, pos.y - FRAME_WIDTH * 11 / 9, std::string(name).length() * 30, 60);
        nameText->draw(NULL, &dst2, 1.0f);
        delete nameText;
    }
}