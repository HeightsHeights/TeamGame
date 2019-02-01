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

#include "../../common/gameData/cObjectData.h"
#include "../../common/gameData/cCharaData.h"

/******************************************************************************
 * class SceneMainGame
 * 機能1：
 * 機能2：
******************************************************************************/

class SceneMainGame : public BaseScene
{
private:
  Character *mush;
  Character *bamboo;

  ObjRawModel *objects[OBJECT_NUMBER];

  GuiSprite *explosion;
  GuiSprite *falleff;
  Particle *trialpart;

  TeamStatus tStatus[TEAM_NUMBER];
  StatusDrawer *statusDrawer;

  Vector3f lookMove;
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