#include "./sceneMainGame.h"

#include "../render/shader/shaderManager.h"

#define PNG_DIR_PATH "./data/res/gui/image/"
#define PNG_FILE_EXTENSION ".png"

static const SDL_Color gRed = {0, 0, 255, 0};
Gamebuff SceneMainGame::gb[StatusDrawer::CHARA_NUMBER];

SceneMainGame::SceneMainGame(WindowManager *window) : BaseScene(window)
{
}
SceneMainGame::SceneMainGame(WindowManager *window, ConfigData *config) : BaseScene(window, config)
{
}
bool SceneMainGame::init()
{
    skybox = ObjModelLoader().load("./data/res/gui/obj/cube/", "cube");
    tile = ObjModelLoader().load("./data/res/gui/obj/map/", "map");
    mush = new Character("./data/res/gui/obj/kinokochara/", "kinoko", NULL);
    bamboo = ObjModelLoader().load("./data/res/gui/obj/bambooshootchara/", "bambooshootchara");
    sprite = GuiSpriteLoader().load("./data/res/gui/image/effect/magic_R.png", 1, 1);
    trialpart = ParticleLoader().load("./data/res/gui/image/effect/slash.png", 3, 3, 1000);
    android = ObjModelLoader().load("./data/res/gui/obj/", "test");

    particle_emission == 0;
    for (int i = 0; i < StatusDrawer::CHARA_NUMBER; i++)
    {
        for (int j = 0; j < BUFF_NUMBER; j++)
        {
            gb[i].buff[j] = false;
        }
    }
    statusDrawer = new StatusDrawer();
    if (!statusDrawer->init())
    {
        return false;
    }

    mushEye = Vector3f(1, 0, 1);

    return true;
}
SCENE_ID SceneMainGame::reactController(ControllerParam param)
{
    mush->move(Vector3f(param.axisL.x, 0.0f, param.axisL.y));
    if (param.buttonDown[CT_DECITION_OR_ATTACK] == true && particle_emission == 0)
    {
        particle_emission = 1;
        trialpart->generate(100);
    }
    if (param.buttonUp[CT_DECITION_OR_ATTACK] == true)
        particle_emission = 0;
    return SI_MAIN;
}
SCENE_ID SceneMainGame::executeCommand(int command)
{
    return SI_MAIN;
}

void SceneMainGame::draw3D()
{

    gluPerspective(60, WINDOW_WIDTH / WINDOW_HEIGHT, 1.0, 500);

    gluLookAt(mush->transform.position.x, 150, 100 + mush->transform.position.z, mush->transform.position.x, 0, mush->transform.position.z, 0, 1, 0);

    float lightPos[] = {0, 100, 0, 1};
    glLightfv(GL_LIGHT0, GL_POSITION, lightPos);

    ShaderManager::startShader(SID_TEXTURING);
    glPushMatrix();
    glScalef(180.0f, 90.0f, 90.0f);
    skybox->draw();
    glPopMatrix();
    ShaderManager::stopShader(SID_TEXTURING);

    ShaderManager::startShader(SID_T_PHONG);
    glPushMatrix();
    glTranslatef(0.0f, 18.0f, 0.0f);
    glScalef(16.0f, 16.0f, 16.0f);
    android->draw();
    glPopMatrix();

    glPushMatrix();
    glScalef(20.0f, 1.0f, 10.0f);
    tile->draw();
    glPopMatrix();
    ShaderManager::stopShader(SID_T_PHONG);

    ShaderManager::startShader(SID_NT_PHONG);

    // glPushMatrix();
    // glScalef(1.0f, 2.0f, 1.0f);
    // glTranslatef(positionMush.x, 0, positionMush.y);

    // lookatVector(mushEye - Vector3f(positionMush.x, 0, positionMush.y));
    mush->draw();
    // glPopMatrix();

    glPushMatrix();
    // glScalef(1.6f, 1.6f, 1.6f);

    glTranslatef(mushEye.x, 0, mushEye.y);

    //bamboo->draw();
    glPopMatrix();

    ShaderManager::stopShader(SID_NT_PHONG);

    static int i = 0;
    ShaderManager::startShader(SID_BILLBOARD);
    glPushMatrix();
    glTranslatef(positionMush.x, 0, positionMush.y);
    glRotated(i++, 0, 1, 0);
    GuiRect dst = GuiRect(0, 0, 50, 50);
    sprite->draw(0, &dst, 1.0f, Vector3f(-25, 15, 0));

    glPopMatrix();
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

    statusDrawer->draw(Vector2f(-475, -200), StatusDrawer::COLOR_RED, 10, true, "suyama");
    statusDrawer->draw(Vector2f(-225, -200), StatusDrawer::COLOR_BLUE, 00, false, "SUYAMA");
    statusDrawer->draw(Vector2f(25, -200), StatusDrawer::COLOR_YELLOW, 44, true, "sym");
    statusDrawer->draw(Vector2f(275, -200), StatusDrawer::COLOR_GREEN, 555, true, "SYM");
    statusDrawer->drawTeamStatus(Vector2f(-465, 310), StatusDrawer::CHARA_MUSH, 200, gb[StatusDrawer::CHARA_MUSH]);
    statusDrawer->drawTeamStatus(Vector2f(65, 310), StatusDrawer::CHARA_BAMBOO, 100, gb[StatusDrawer::CHARA_BAMBOO]);
    ShaderManager::stopShader(SID_GUI);
}

void SceneMainGame::lookatVector(Vector3f direction)
{
    direction.y = 0;

    Vector3f vecY = Vector3f(0, 1, 0);
    Vector3f vecZ = Vector3f(0, 0, 1);

    float theta = direction.betweenAngleDegree(vecZ);
    if (Vector3f::cross(vecZ, direction).y < 0)
    {
        theta *= -1;
    }
    glRotated(theta, vecY.x, vecY.y, vecY.z);
}
