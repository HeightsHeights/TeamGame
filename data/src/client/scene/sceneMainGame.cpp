#include "./sceneMainGame.h"

#include "../../common/network/dataBlock/dataBlock.h"
#include "../../common/network/networkCommand.h"
#include "../network/networkManager.h"
#include "../render/shader/shaderManager.h"

#define PNG_DIR_PATH "./data/res/gui/image/"
#define PNG_FILE_EXTENSION ".png"

#define OBJ_DIR_PATH "./data/res/gui/obj/"

// static const SDL_Color gRed = {0, 0, 255, 0};

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
    };

    std::string objName[OBJECT_NUMBER] = {
        "cube",
        "map",
        "redtower",
        "bluetower",
        "obb",
        "sphere",
    };

    for (int i = 0; i < OBJECT_NUMBER; i++)
    {
        objects[i] = ObjModelLoader().load(OBJ_DIR_PATH + objFileDir[i], objName[i]);
        if (objects[i] == NULL)
        {
            return false;
        }
    }

    gameObjects = Object(&objects[0]);

    mush = new Character("./data/res/gui/obj/kinokochara/", "kinoko", NULL);
    bamboo = new Character("./data/res/gui/obj/bambooshootchara/", "bambooshoot", NULL);

    object = ObjModelLoader().load("./data/res/gui/obj/jewelry/", "sapphire");
    trialpart = ParticleLoader().load("./data/res/gui/image/effect/slash.png", 3, 3, 1000);
    clash = GuiSpriteLoader().load("./data/res/gui/image/effect/clash.png", 1, 1);

    particle_emission == 0;
    atkmode = false;

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
    if (param.buttonDown[CT_DECITION_OR_ATTACK] && particle_emission == 0)
    {
        atkmode = true;

        particle_emission = 1;
        trialpart->generate(15);
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
    ShaderManager::stopShader(SID_T_PHONG);

    ShaderManager::startShader(SID_NT_PHONG);
    glPushMatrix();
    glTranslatef(15.0f, 1.0f, 15.0f);
    glScalef(0.025f, 0.05f, 0.025f);
    gameObjects.getModelP(OBJECT_TOWER_R)->draw();
    glPopMatrix();

    //Charactor
    mush->draw();
    bamboo->draw();
    //Weapon

    //Object
    glPushMatrix();
    // glTranslatef(0.0f, 10.0f, 0.0f);
    // glScalef(10.0f, 12.0f, 10.0f); //クリスタル
    // object->draw();

    glTranslatef(-20.0f, 0.0f, 20.0f);
    glScalef(5.0f, 12.0f, 5.0f); //宝石
    object->draw();

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
    glTranslatef(5, 40, 10);

    statusDrawer->drawTeamStatus(Vector2f(0, 0), TEAM_BAMBOO, TeamStatus(), Vector3f(0, 0, 0));

    glPopMatrix();

    // clash->draw(0, &dst, 1.0f, Vector3f(-50, 50, 0));
    ShaderManager::stopShader(SID_BILLBOARD);

    ShaderManager::startShader(SID_PARTICLE);
    glPushMatrix();
    trialpart->draw(1.0f);
    glPopMatrix();
    ShaderManager::stopShader(SID_PARTICLE);
}
void SceneMainGame::draw2D()
{
    ShaderManager::startShader(SID_GUI);
    statusDrawer->draw(Vector2f(-475, -200), TEAM_MUSH, 10, true, "suyama");
    statusDrawer->draw(Vector2f(-225, -200), TEAM_BAMBOO, 00, false, "SUYAMA");
    statusDrawer->draw(Vector2f(25, -200), TEAM_MUSH, 888, false, "sym");
    statusDrawer->draw(Vector2f(275, -200), TEAM_BAMBOO, 555, true, "SYM");
    statusDrawer->drawTeamStatus(Vector2f(-465, 310), TEAM_MUSH, TeamStatus());
    statusDrawer->drawTeamStatus(Vector2f(65, 310), TEAM_BAMBOO, TeamStatus());
    ShaderManager::stopShader(SID_GUI);
}
