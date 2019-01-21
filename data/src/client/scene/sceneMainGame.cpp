#include "./sceneMainGame.h"

#include "../render/shader/shaderManager.h"

#define PNG_DIR_PATH "./data/res/gui/image/"
#define PNG_FILE_EXTENSION ".png"

static const SDL_Color gRed = {0, 0, 255, 0};

SceneMainGame::SceneMainGame(WindowManager *window) : BaseScene(window)
{
}
SceneMainGame::SceneMainGame(WindowManager *window, ConfigData *config) : BaseScene(window, config)
{
}
bool SceneMainGame::init()
{
    tile = ObjModelLoader().load("./data/res/gui/obj/", "tile");
    mush = ObjModelLoader().load("./data/res/gui/obj/kinokochara/", "kinokochara");

   sprite = GuiSpriteLoader().load("./data/res/gui/image/effect/magic_R.png", 1, 1);

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
    positionMush += Vector2f(param.axisL.x * 0.1, param.axisL.y * 0.1);
    return SI_MAIN;
}
SCENE_ID SceneMainGame::executeCommand(int command)
{
    return SI_MAIN;
}
void SceneMainGame::draw3D()
{

    gluPerspective(60, WINDOW_WIDTH / WINDOW_HEIGHT, 1.0, 200);

    gluLookAt(positionMush.x, 100, 30 + positionMush.y, positionMush.x, 0, positionMush.y, 0, 1, 0);
    float lightPos[] = {0, 100, 0, 1};
    glLightfv(GL_LIGHT0, GL_POSITION, lightPos);

    ShaderManager::startShader(SID_NT_PHONG);

    glPushMatrix();
    glScalef(10.0f, 1.0f, 10.0f);
    tile->draw();
    glPopMatrix();

    glPushMatrix();
    glScalef(1.0f, 2.0f, 1.0f);
    glTranslatef(positionMush.x, 0, positionMush.y);

    lookatVector(mushEye - Vector3f(positionMush.x, 0, positionMush.y));
    mush->draw();
    glPopMatrix();

    glPushMatrix();
    glScalef(1.0f, 2.0f, 1.0f);
    glTranslatef(mushEye.x, 0, mushEye.y);
    mush->draw();
    glPopMatrix();

    ShaderManager::stopShader(SID_NT_PHONG);

static int i = 0 ;
    ShaderManager::startShader(SID_BILLBOARD);
    glPushMatrix();
    glTranslatef(positionMush.x, 0, positionMush.y);
    glRotated(i++,0,1,0);
    GuiRect dst = GuiRect(0, 0, 50, 50);
    sprite->draw(0, &dst, 1.0f,Vector3f(-25, 15, 0));
    glPopMatrix();
    ShaderManager::stopShader(SID_BILLBOARD);


}
void SceneMainGame::draw2D()
{
    ShaderManager::startShader(SID_GUI);

    statusDrawer->draw(Vector2f(-475, -200), StatusDrawer::COLOR_RED, 10, true, "suyama");
    statusDrawer->draw(Vector2f(-225, -200), StatusDrawer::COLOR_BLUE, 00, false, "SUYAMA");
    statusDrawer->draw(Vector2f(25, -200), StatusDrawer::COLOR_YELLOW, 44, true, "sym");
    statusDrawer->draw(Vector2f(275, -200), StatusDrawer::COLOR_GREEN, 555, true, "SYM");
    statusDrawer->drawTeamStatus(Vector2f(-465, 310), StatusDrawer::CHARA_MUSH, 200,true,false,true);
    statusDrawer->drawTeamStatus(Vector2f(65, 310), StatusDrawer::CHARA_BAMBOO, 100,false,true,false);
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
