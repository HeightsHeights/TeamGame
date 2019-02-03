#include "./sceneMainGame.h"

#include "../../common/network/dataBlock/dataBlock.h"
#include "../../common/network/networkCommand.h"
#include "../network/networkManager.h"
#include "../render/shader/shaderManager.h"

#define PNG_DIR_PATH "./data/res/gui/image/"
#define PNG_FILE_EXTENSION ".png"

#define OBJ_DIR_PATH "./data/res/gui/obj/"

SceneMainGame::SceneMainGame(WindowManager *window) : BaseScene(window)
{
}
SceneMainGame::SceneMainGame(WindowManager *window, ConfigData *config) : BaseScene(window, config)
{
}
bool SceneMainGame::init()
{

    const std::string spriteName[EFFECT_NUMBER] = {
        "effect/explosion",
        "effect/death",
        "effect/death",
    };

    const unsigned int spriteDivisionNum[EFFECT_NUMBER][2] = {
        {7, 1},
        {8, 1},
        {8, 1},
    };

    for (int i = 0; i < EFFECT_NUMBER; i++)
    {
        sprites[i] = GuiSpriteLoader().load((PNG_DIR_PATH + spriteName[i] + PNG_FILE_EXTENSION).c_str(), spriteDivisionNum[i][0], spriteDivisionNum[i][1]);
        if (sprites[i] == NULL)
        {
            return false;
        }
    }

    const std::string objFileDir[OBJECT_NUMBER] = {
        "cube/",
        "map/",
        "tower/",
        "tower/",
        "object/",
        "object/",
        "object/",
        "weapon/",
        "jewelry/",
        "jewelry/",
        "jewelry/",
        "kinokochara/",
        "bambooshootchara/",
        "kinokochara/",
        "collider/",
        "collider/",
    };
    const std::string objName[OBJECT_NUMBER] = {
        "cube",
        "led",
        "redtower",
        "bluetower",
        "block_R",
        "block_B",
        "block",
        "bomb",
        "ruby",
        "sapphire",
        "emerald",
        "kinoko",
        "bambooshoot",
        "hand",
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

    Transform skyboxTransform = Transform(Vector3f(), Vector3f_ZERO, Vector3f(220.0f, 90.0f, 170.0f));
    skybox = CObjectData(OBJECT_SKYBOX, true, &skyboxTransform);

    trialpart = ParticleLoader().load("./data/res/gui/image/effect/slash.png", 3, 3, 1000);
    explosion = GuiSpriteLoader().load("./data/res/gui/image/effect/explosion.png", 7, 1);
    falleff = GuiSpriteLoader().load("./data/res/gui/image/effect/death.png", 8, 1);

    for (int i = 0; i < TEAM_NUMBER; i++)
    {
        tStatus[i] = TeamStatus();
    }

    objectDrawer = new ObjectDrawer(&objects[0]);
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
    else if (command == NC_SEND_RESULT_DATA)
    {
        int id;
        NetworkManager::recvData(&id, sizeof(int));
        NetworkManager::recvData(&charaData[id], sizeof(CCharaData));
    }
    else if (command == NC_SEND_OBJECT_DATA)
    {
        int id;
        OBJECT_TYPE type;
        CObjectData data;

        NetworkManager::recvData(&id, sizeof(int));
        NetworkManager::recvData(&type, sizeof(OBJECT_TYPE));
        NetworkManager::recvData(&data, sizeof(CObjectData));

        if (type == OBJECT_TYPE_STATIC)
        {
            staticObjectData[id] = data;
        }
        else if (type == OBJECT_TYPE_DYNAMIC)
        {
            dynamicObjectData[id] = data;
        }
    }
    else if (command == NC_SEND_EFFECT_DATA)
    {
        EFFECT_ID id;
        Vector3f position;
        NetworkManager::recvData(&id, sizeof(EFFECT_ID));
        NetworkManager::recvData(&position, sizeof(Vector3f));

        for (int i = 0; i < MAX_EFFECT; i++)
        {
            EffectData *pEffect = &effects[i];
            if (pEffect->exist)
            {
                continue;
            }
            *pEffect = EffectData(id, position, 10);
            break;
        }
    }
    else if (command == NC_SEND_RESULT_DATA)
    {
        // NetworkManager::recvData(&gResult, sizeof(GameResult));
    }
    return nextScene;
}

void SceneMainGame::draw3D()
{
    gluPerspective(60, WINDOW_WIDTH / WINDOW_HEIGHT, 1.0, 800);

    cameraMove();

    float lightPos[] = {0, 1000, 300, 1};
    glLightfv(GL_LIGHT0, GL_POSITION, lightPos);

    ShaderManager::startShader(SID_TEXTURING);
    //skybox
    objectDrawer->drawObject(skybox);
    ShaderManager::stopShader(SID_TEXTURING);

    ShaderManager::startShader(SID_T_PHONG);
    //Tile
    objectDrawer->drawObject(staticObjectData[0]);

    //色付き壁
    for (int i = SOBJECT_WALL_R1; i <= SOBJECT_WALL_B2; i++)
    {
        objectDrawer->drawObject(staticObjectData[i]);
    }
    ShaderManager::stopShader(SID_T_PHONG);

    ShaderManager::startShader(SID_NT_PHONG);
    //タワー
    for (int i = SOBJECT_TOWER_R; i <= SOBJECT_TOWER_B; i++)
    {
        objectDrawer->drawObject(staticObjectData[i]);
    }
    //中央壁
    objectDrawer->drawObject(staticObjectData[7]);
    //Charactor
    for (int i = 0; i < MAX_PLAYERS; i++)
    {
        objectDrawer->drawChara(charaData[i]);
    }
    //Dynamic
    for (int i = 0; i < MAX_DYNAMIC_OBJECTS; i++)
    {
        if (!dynamicObjectData[i].exist)
        {
            continue;
        }
        objectDrawer->drawObject(dynamicObjectData[i]);
    }

    //Collider
    // for (int i = 0; i < MAX_PLAYERS; i++)
    // {
    //     objectDrawer->drawCollider(charaData[i].mainBodyData.collider);
    // }
    // for (int i = SOBJECT_TILE; i < SOBJECT_NUMBER; i++)
    // {
    //     objectDrawer->drawCollider(staticObjectData[i].collider);
    // }
    // for (int i = 0; i < MAX_DYNAMIC_OBJECTS; i++)
    // {
    //     if (!dynamicObjectData[i].exist)
    //     {
    //         continue;
    //     }
    //     objectDrawer->drawCollider(dynamicObjectData[0].collider);
    // }
    ShaderManager::stopShader(SID_NT_PHONG);

    ShaderManager::startShader(SID_BILLBOARD);
    //TowerStatus
    glPushMatrix();
    glTranslatef(115, 50, -10);
    statusDrawer->drawTeamStatus(Vector2f(0, 0), TEAM_BAMBOO, tStatus[TEAM_BAMBOO], Vector3f(0, 0, 0));
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-150, 50, -10);
    statusDrawer->drawTeamStatus(Vector2f(0, 0), TEAM_MUSH, tStatus[TEAM_MUSH], Vector3f(0, 0, 0));
    glPopMatrix();
    // if (explosioon_emission == 1)
    // {
    //     static int w;
    //     if (w > 8)
    //         w = 0;
    //     GuiRect dst = {0, 0, 100, 100};
    //     explosion->draw(w++, &dst, 1.0f, Vector3f(-100, 100, 0));
    //     if (w == 8)
    //         explosioon_emission = 0;
    // }
    // falleff->draw(w++, &dst, 1.0f, Vector3f(-100, 100, 0));

    for (int i = 0; i < MAX_EFFECT; i++)
    {
        EffectData *pEffect = &effects[i];
        if (pEffect->exist)
        {
            continue;
        }
        pEffect->update();
        if (pEffect->exist)
        {
            objectDrawer->drawEffect(*pEffect, &sprites[0]);
        }
    }
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
    statusDrawer->drawReadySignal(SIGNAL_NULL);
    for (int i = 0; i < MAX_PLAYERS; i++)
    {
        CCharaData *pChara = &charaData[i];
        statusDrawer->draw(Vector2f(-475 + 250 * i, -200), pChara->teamId, pChara->hp, (pChara->hp == 0) ? false : true, BaseScene::players[i].name);
    }

    statusDrawer->drawTeamStatus(Vector2f(-465, 310), TEAM_MUSH, tStatus[TEAM_MUSH]);
    statusDrawer->drawTeamStatus(Vector2f(65, 310), TEAM_BAMBOO, tStatus[TEAM_BAMBOO]);
    statusDrawer->drawResult(RESULT_NULL);
    if (charaData[myId].hp == 0)
    {
        statusDrawer->drawDeadMessage(1.0f, charaData[myId].spawningTime);
    }
    ShaderManager::stopShader(SID_GUI);
}
void SceneMainGame::cameraMove()
{
    Vector3f *pMyCharaPos = &charaData[myId].transform.position;
    if (pMyCharaPos->x > -150 && pMyCharaPos->x < 150 && pMyCharaPos->z < 75)
    {
        gluLookAt(pMyCharaPos->x, 150, 100 + pMyCharaPos->z, pMyCharaPos->x, 0, pMyCharaPos->z, 0, 1, 0);
        lookMove = *pMyCharaPos;
    }
    else
    {
        gluLookAt(lookMove.x, 150, 100 + lookMove.z, lookMove.x, 0, lookMove.z, 0, 1, 0);
    }
}