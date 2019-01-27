#pragma once

/******************************************************************************
 * maingame関係に必要なヘッダーの読み込み
******************************************************************************/
#include "./sceneBase.h"

#include "../render/objRawModel/objModelLoader.h"
#include "./mainGame/statusDrawer.h"
#include "../render/gui/sprite/guiSpriteLoader.h"
#include "../render/particle/particleLoader.h"
#include "../gameObject/character/character.h"

/******************************************************************************
 * class SceneMainGame
 * 機能1：
 * 機能2：
******************************************************************************/

class SceneMainGame : public BaseScene
{

public:
  typedef enum
  {
    OBJECT_SKYBOX = 0,
    OBJECT_TILE = 1,
    OBJECT_TOWER_R = 2,
    OBJECT_TOWER_B = 3,
    OBJECT_DEBUG_OBB = 4,
    OBJECT_DEBUG_SPHERE = 5,
    OBJECT_NUMBER = 6,
  } OBJECT_ID;

  class Object
  {
  private:
    static ObjRawModel **models;
    static bool initable;

  public:
    Object() {}
    Object(ObjRawModel **models)
    {
      if (initable)
      {
        Object::models = models;
        initable = false;
      }
    }

    ObjRawModel *getModelP(OBJECT_ID id) { return *(models + id); }
    SceneMainGame::OBJECT_ID id;
    Transform transform;
  };

private:
  Character *mush;
  Character *bamboo;

  ObjRawModel *objects[OBJECT_NUMBER];

  Object gameObjects;

  ObjRawModel *skybox;
  ObjRawModel *tile;
  ObjRawModel *tower;
  ObjRawModel *collisionO;
  ObjRawModel *collisionS;

  ObjRawModel *object;

  GuiSprite *clash;
  Particle *trialpart;

  StatusDrawer *statusDrawer;

  int particle_emission;
  bool atkmode;

  virtual void draw3D();
  virtual void draw2D();

public:
  SceneMainGame() : BaseScene() {}
  SceneMainGame(WindowManager *window);
  SceneMainGame(WindowManager *window, ConfigData *config);

  virtual bool init();
  virtual SCENE_ID reactController(ControllerParam param);
  virtual SCENE_ID executeCommand(int command);
};