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
    sprite = GuiSpriteLoader().load("./data/res/gui/image/effe/m/pipo-btleffect133.png", 3, 3);
    tile = ObjModelLoader().load("./data/res/gui/obj/", "tile");
    mush = ObjModelLoader().load("./data/res/gui/obj/kinokochara/", "kinokochara");
    bamboo = ObjModelLoader().load("./data/res/gui/obj/", "bambooshootchara");
    Uhono = ObjModelLoader().load("./data/res/gui/obj/", "bardicheWithMaterial");
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

    gluLookAt(positionMush.x, 20, 30 + positionMush.y, positionMush.x, 0, positionMush.y, 0, 1, 0);
    float lightPos[] = {0, 100, 0, 1};
    glLightfv(GL_LIGHT0, GL_POSITION, lightPos);

    ShaderManager::startShader(SID_STATIC);

    glPushMatrix();
    glScalef(10.0f, 1.0f, 10.0f);
    tile->draw();
    glPopMatrix();

    glPushMatrix();
    glScalef(1.0f, 2.0f, 1.0f);
    glTranslatef(positionMush.x, 0, positionMush.y);
    // lookatVector(mushEye - Vector3f(positionMush.x, 0, positionMush.y));
    glRotated(-35, 0, 1, 0);
    mush->draw();
    glPopMatrix();

    glPushMatrix();
    glScalef(2.0f, 4.0f, 2.0f);
    glRotated(290, 0, 1, 0);
    glTranslatef(mushEye.x, 0, mushEye.y);
    bamboo->draw();
    glPopMatrix();

    glPushMatrix();
    glScalef(1.6f, 1.6f, 1.6f);
    glTranslatef(positionMush.x, 1.0, positionMush.y + 3.5);
    glRotated(-60, 0, 0, 1);
    // lookatVector(mushEye - Vector3f(positionMush.x, 0, positionMush.y));
    Uhono->draw();
    glPopMatrix();

    ShaderManager::stopShader(SID_STATIC);
}
void SceneMainGame::draw2D()
{
    ShaderManager::startShader(SID_GUI);

    static int rotate;

    GuiRect rect = GuiRect(300, 250, 300, 300);
    sprite->draw(rotate, &rect);

    if (rotate++ > 9)
    {
        rotate = 0;
    }
    statusDrawer->draw(Vector2f(-475, -200), StatusDrawer::COLOR_RED, 10, true, "SYM");
    statusDrawer->draw(Vector2f(-225, -200), StatusDrawer::COLOR_BLUE, 00, false, "YSD");
    statusDrawer->draw(Vector2f(25, -200), StatusDrawer::COLOR_YELLOW, 44, true, "TNOK");
    statusDrawer->draw(Vector2f(275, -200), StatusDrawer::COLOR_GREEN, 555, true, "MZN");
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