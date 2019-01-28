#include "./sceneMainGame.h"

#include "../../common/network/dataBlock/dataBlock.h"
#include "../../common/network/networkCommand.h"
#include "../network/networkManager.h"
#include "../render/shader/shaderManager.h"

#define PNG_DIR_PATH "./data/res/gui/image/"
#define PNG_FILE_EXTENSION ".png"

#define OBJ_DIR_PATH "./data/res/gui/obj/"

static const SDL_Color gRed = {0, 0, 255, 0};

ObjRawModel **SceneMainGame::Object::models;
bool SceneMainGame::Object::initable = true;

SceneMainGame::SceneMainGame(WindowManager *window) : BaseScene(window)
{
}
SceneMainGame::SceneMainGame(WindowManager *window, ConfigData *config) : BaseScene(window, config)
{
}
bool SceneMainGame::init()
{
    const std::string objFileDir[OBJECT_NUMBER] = {
        "cube/",
        "map/",
        "tower/",
        "tower/",
        "collider/",
        "collider/",
        "object/",
        "object/",
        "object/",
        "weapon/",
        "jewelry/",
    };

    std::string objName[OBJECT_NUMBER] = {
        "cube",
        "map",
        "redtower",
        "bluetower",
        "obb",
        "sphere",
        "block_R",
        "block_B",
        "block",
        "bomb",
        "ruby",
    };

    for (int i = 0; i < OBJECT_NUMBER; i++)
    {
        objects[i] = ObjModelLoader().load(OBJ_DIR_PATH + objFileDir[i], objName[i]);
        if (objects[i] == NULL)
        {
            return false;
        }
    }

    text[0] = GuiTextLoader().load(FID_NORMAL, "3", gRed);
    text[1] = GuiTextLoader().load(FID_NORMAL, "2", gRed);
    text[2] = GuiTextLoader().load(FID_NORMAL, "1", gRed);
    text[3] = GuiTextLoader().load(FID_NORMAL, "LOSE", gRed);
    text[4] = GuiTextLoader().load(FID_NORMAL, "WIN", gRed);

    gameObjects = Object(&objects[0]);

    mush = new Character("./data/res/gui/obj/kinokochara/", "kinoko", NULL);
    bamboo = new Character("./data/res/gui/obj/bambooshootchara/", "bambooshoot", NULL);

    object = ObjModelLoader().load("./data/res/gui/obj/jewelry/", "sapphire");
    trialpart = ParticleLoader().load("./data/res/gui/image/effect/slash.png", 3, 3, 1000);
    explosion = GuiSpriteLoader().load("./data/res/gui/image/effect/explosion.png", 7, 1);
    falleff = GuiSpriteLoader().load("./data/res/gui/image/effect/death.png", 8, 1);

    explosioon_emission == 0;
    atkmode = false;

    for (int i = 0; i < TEAM_NUMBER; i++)
    {
        tStatus[i] = TeamStatus();
    }

    statusDrawer = new StatusDrawer();
    if (!statusDrawer->init())
    {
        return false;
    }

    return true;
}
SCENE_ID SceneMainGame::reactController(ControllerParam param)
{
    DataBlock data;
    data.setCommand2DataBlock(NC_SEND_CONTROLLER_PARAM);
    data.setData(&param, sizeof(ControllerParam));
    NetworkManager::sendData(data, data.getDataSize());

    mush->move(Vector3f(param.axisL.x, 0.0f, param.axisL.y));
    if (param.buttonDown[CT_DECITION_OR_ATTACK] && explosioon_emission == 0)
    {
        atkmode = true;

        explosioon_emission = 1;
        // trialpart->generate(15);
    }
    if (atkmode)
    {
        static int atk;
        mush->motion(Character::MOTION_ATTACK, atk++);

        if (atk > 45)
        {
            mush->motion(Character::MOTION_NULL, 0);
            atk = 0;
            atkmode = false;
        }
    }

    if (param.buttonDown[CT_GRUB] == true)
    {
        static int time;
        mush->motion(Character::MOTION_THROW, time++);
    }
    {
        mush->motion(Character::MOTION_NULL, 0);
    }

    return SI_MAIN;
}
SCENE_ID SceneMainGame::executeCommand(int command)
{
    SCENE_ID nextScene = SI_MAIN;
    if (command == NC_FINISH)
    {
        nextScene = SI_NUMBER;
    }
    else if (command == NC_SEND_TEAM_STATUS)
    {
        TEAM_ID id;
        NetworkManager::recvData(&id, sizeof(TEAM_ID));
        NetworkManager::recvData(&tStatus[id], sizeof(TeamStatus));
    }

    // if (command == drawcll)
    // {
    //     NetworkManager::recvData(&id, )
    // }
    return nextScene;
}

void SceneMainGame::draw3D()
{

    gluPerspective(60, WINDOW_WIDTH / WINDOW_HEIGHT, 1.0, 800);

    gluLookAt(mush->transform.position.x, 150, 100 + mush->transform.position.z, mush->transform.position.x, 0, mush->transform.position.z, 0, 1, 0);

    float lightPos[] = {0, 100, 0, 1};
    glLightfv(GL_LIGHT0, GL_POSITION, lightPos);

    //skyBox
    ShaderManager::startShader(SID_TEXTURING);
    glPushMatrix();
    glScalef(180.0f, 90.0f, 135.0f);
    gameObjects.getModelP(OBJECT_SKYBOX)->draw();
    glPopMatrix();
    ShaderManager::stopShader(SID_TEXTURING);

    //Tile
    ShaderManager::startShader(SID_T_PHONG);
    glPushMatrix();
    glScalef(20.0f, 1.0f, 10.0f);
    gameObjects.getModelP(OBJECT_TILE)->draw();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-100.0, 10.0, 40);
    glScalef(10.0f, 10.0f, 10.0f);
    gameObjects.getModelP(OBJECT_BLOCK_R)->draw();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-65.0, 10.0, -40);
    glScalef(10.0f, 10.0f, 10.0f);
    gameObjects.getModelP(OBJECT_BLOCK_R)->draw();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(85.0, 10.0, -40);
    glScalef(10.0f, 10.0f, 10.0f);
    gameObjects.getModelP(OBJECT_BLOCK_B)->draw();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(50.0, 10.0, 40);
    glScalef(10.0f, 10.0f, 10.0f);
    gameObjects.getModelP(OBJECT_BLOCK_B)->draw();
    glPopMatrix();

    ShaderManager::stopShader(SID_T_PHONG);

    ShaderManager::startShader(SID_NT_PHONG);
    glPushMatrix();
    glTranslatef(-140.0f, 1.0f, 0.0f);
    glScalef(0.03f, 0.07f, 0.03f);
    gameObjects.getModelP(OBJECT_TOWER_R)->draw();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(125.0f, 1.0f, 0.0f);
    glScalef(0.03f, 0.07f, 0.03f);
    gameObjects.getModelP(OBJECT_TOWER_B)->draw();
    glPopMatrix();

    //Charactor
    mush->draw();
    bamboo->draw();
    //Weapon

    //Object

    glPushMatrix();
    glTranslatef(0.0, 10.0, 0.0);
    glScalef(10.0f, 10.0f, 10.0f);
    gameObjects.getModelP(OBJECT_BLOCK_NORMAL)->draw();
    glPopMatrix();

    //壁当たり判定
    // glPushMatrix();
    // glTranslatef(0.0f, 10.0f, 0.0f);
    // glScalef(1.6f, 15.0f, 20.0f);
    // gameObjects.getModelP(OBJECT_DEBUG_OBB)->draw();
    // glPopMatrix();

    //タワー当たり判定
    // glPushMatrix();
    // glTranslatef(-140.0f, 20.0f, 0.0f);
    // glScalef(3.0f, 20.0f, 3.0f);
    // gameObjects.getModelP(OBJECT_DEBUG_OBB)->draw();
    // glPopMatrix();

    // glTranslatef(0.0f, 10.0f, 0.0f);
    // glScalef(10.0f, 12.0f, 10.0f); //クリスタル
    // object->draw();

    glPushMatrix();
    glTranslatef(10.0f, 10.0f, 30.0f);
    glScalef(2.0f, 2.0f, 2.0f);
    gameObjects.getModelP(OBJECT_BOMB)->draw();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(16.0f, 0.0f, 31.0f);
    glScalef(5.6f, 8.7f, 5.6f); //宝石
    gameObjects.getModelP(OBJECT_RUBY)->draw();

    // glScalef(5.0f, 12.0f, 5.0f); //石１
    // object->draw();

    // glScalef(8.0f, 12.0f, 8.0f); //石２
    // object->draw();

    // glScalef(8.0f, 12.0f, 8.0f); //石３
    // object->draw();

    // glScalef(5.0f, 12.0f, 5.0f); //木
    // object->draw();
    glPopMatrix();
    ShaderManager::stopShader(SID_NT_PHONG);

    ShaderManager::startShader(SID_BILLBOARD);
    glPushMatrix();
    glTranslatef(115, 50, -10);
    statusDrawer->drawTeamStatus(Vector2f(0, 0), TEAM_BAMBOO, tStatus[TEAM_BAMBOO], Vector3f(0, 0, 0));
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-150, 50, -10);
    statusDrawer->drawTeamStatus(Vector2f(0, 0), TEAM_MUSH, tStatus[TEAM_MUSH], Vector3f(0, 0, 0));
    glPopMatrix();
    if (explosioon_emission == 1)
    {
        static int w;
        if (w > 8)
            w = 0;
        GuiRect dst = {0, 0, 100, 100};
        explosion->draw(w++, &dst, 1.0f, Vector3f(-100, 100, 0));
        if (w == 8)
            explosioon_emission = 0;
    }
    // falleff->draw(w++, &dst, 1.0f, Vector3f(-100, 100, 0));
    ShaderManager::stopShader(SID_BILLBOARD);

    // ShaderManager::startShader(SID_PARTICLE);
    // glPushMatrix();
    // trialpart->draw(1.0f);
    // glPopMatrix();
    // ShaderManager::stopShader(SID_PARTICLE);
}
void SceneMainGame::draw2D()
{
    ShaderManager::startShader(SID_GUI);
    dst[0] = GuiRect(-50.0f, 50.0f, 50.0f, 50.0f);
    // text[0]->draw(NULL, &dst[0], 1.0f);
    // text[1]->draw(NULL, &dst[0], 1.0f);
    // text[2]->draw(NULL, &dst[0], 1.0f);
    statusDrawer->draw(Vector2f(-475, -200), TEAM_MUSH, 10, true, "suyama");
    statusDrawer->draw(Vector2f(-225, -200), TEAM_BAMBOO, 00, false, "SUYAMA");
    statusDrawer->draw(Vector2f(25, -200), TEAM_MUSH, 888, false, "sym");
    statusDrawer->draw(Vector2f(275, -200), TEAM_BAMBOO, 555, true, "SYM");
    statusDrawer->drawTeamStatus(Vector2f(-465, 310), TEAM_MUSH, tStatus[TEAM_MUSH]);
    statusDrawer->drawTeamStatus(Vector2f(65, 310), TEAM_BAMBOO, tStatus[TEAM_BAMBOO]);
    dst[1] = GuiRect(-50.0f, 50.0f, 50.0f, 50.0f);
    // text[3]->draw(NULL, &dst[1], 1.0f);
    // text[4]->draw(NULL, &dst[1], 1.0f);
    ShaderManager::stopShader(SID_GUI);
}
