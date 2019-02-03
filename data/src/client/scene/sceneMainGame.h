#pragma once

/******************************************************************************
 * maingame関係に必要なヘッダーの読み込み
******************************************************************************/
#include "./sceneBase.h"

#include "../render/objRawModel/objModelLoader.h"
#include "./mainGame/statusDrawer.h"
#include "../render/gui/sprite/guiSpriteLoader.h"
#include "../render/particle/particleLoader.h"
#include "../../common/math/ringCounter/ringCounter.h"
#include "./mainGame/objectDrawer.h"

/******************************************************************************
 * class SceneMainGame
 * 機能1：
 * 機能2：
******************************************************************************/

class SceneMainGame : public BaseScene
{
private:
  SIGNAL_ID signal;
  ObjRawModel *objects[OBJECT_NUMBER];

  GuiSprite *sprites[EFFECT_NUMBER];
  GuiSprite *explosion;
  GuiSprite *falleff;
  Particle *trialpart;

  CObjectData skybox;
  CCharaData charaData[MAX_PLAYERS];
  CObjectData staticObjectData[SOBJECT_NUMBER];
  CObjectData dynamicObjectData[MAX_DYNAMIC_OBJECTS];
  ObjectDrawer *objectDrawer;
  EffectData effects[MAX_EFFECT];

  TeamStatus tStatus[TEAM_NUMBER];
  StatusDrawer *statusDrawer;

  Vector3f lookMove;

  void cameraMove();
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