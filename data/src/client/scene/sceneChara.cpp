#include "./sceneChara.h"
#include "../render/shader/shaderManager.h"
#include "../../common/network/networkCommand.h"
#include "../../common/network/dataBlock/dataBlock.h"
#include "../network/networkManager.h"
#include "../config/loader/configLoader.h"

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
        decision[i] = false;
        player[i].name = NULL;
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

        if(count == MAX_PLAYER/2)
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

    
    if (mypos.y == 1 && param.buttonDown[CT_DECITION_OR_ATTACK] && !param.buttonState[CT_DECITION_OR_ATTACK])
    {
        DataBlock data;
        data.setCommand2DataBlock(NC_READY);
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
        data.setCommand2DataBlock(NC_CONNECT);
        NetworkManager::sendData(data, data.getDataSize());
    }
    
        DataBlock data;
        data.setCommand2DataBlock(NC_CONTROLLER_INFO);
        data.setData(&param, sizeof(ControllerParam));
        NetworkManager::sendData(data, data.getDataSize());
    

    return SI_CHARASELECT;
}
SCENE_ID SceneChara::executeCommand(int command)
{

    if (command == NC_SERVER_MAINGAME)
    {
        return SI_MAIN;
    }
    else if (command == NC_FINISH)
    {
        return SI_NUMBER;
    }
    else if(command == NC_CONTROLLER_INFO)
    {
        int num;
        NetworkManager::recvData(&num,sizeof(int));
        Vector2f positionData;
        
        NetworkManager::recvData(positionData,sizeof(Vector2f));
        player[num].position.x += positionData.x;
        if(player[num].position.x > 1){
            player[num].position.x = 0;
        }
        else if(player[num].position.x < 0){
            player[num].position.x = 1;
        }
        
    }
    else if (command == NC_SERVER_2_CLIENT)
    {
        int num;
        NetworkManager::recvData(&num, sizeof(int));
        connect[num] = true;
        NetworkManager::recvData(&player[num].subname, sizeof(char *));
        player[num].name = &player[num].subname[0];
    }
    
    count = 0;
    for(int i = 0; i < MAX_PLAYER; i++)
    {
        if(player[i].position.x == 0)
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
    if(count == MAX_PLAYER/2){
        bright = (mypos.y == 1)? 1.0f : 0.7f;
    }
    else
    {
        bright = 0.3f;
    }

    ShaderManager::startShader(SID_GUI);
    image[(int)IMAGE_BAMBOO + (int)mypos.x]->draw(NULL, &dst[IMAGE_BAMBOO], (mypos.y == 0) ? 1.0f : 0.3f);
    drawPlayer(Vector2f(100, 400), (player[0].position.x == 0)? COLOR_RED : COLOR_BLUE, connect[0], decision[0], player[0].name);
    drawPlayer(Vector2f(100, 280), (player[1].position.x == 0)? COLOR_RED : COLOR_BLUE, connect[1], decision[1], player[1].name);
    // drawPlayer(Vector2f(100, 160), (position[2].x == 0)? COLOR_RED : COLOR_BLUE, connect[2], decision[2], player[2].name);
    // drawPlayer(Vector2f(100, 40), (position[3].x == 0)? COLOR_RED : COLOR_BLUE, connect[3], decision[3], player[3].name);
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