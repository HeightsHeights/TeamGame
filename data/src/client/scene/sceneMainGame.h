#pragma once

/******************************************************************************
 * maingame関係に必要なヘッダーの読み込み
******************************************************************************/
#include "./sceneBase.h"

#include "../render/objRawModel/objModelLoader.h"
#include "./mainGame/statusDrawer.h"
#include "../render/gui/sprite/guiSpriteLoader.h"
/******************************************************************************
 * class SceneMainGame
 * 機能1：
 * 機能2：
******************************************************************************/

class SceneMainGame : public BaseScene
{
private:
  ObjRawModel *tile;
  ObjRawModel *mush;
  ObjRawModel *bamboo;
  ObjRawModel *skybox;

  Vector2f positionMush;
  Vector3f mushEye;
  GuiSprite *sprite;

  StatusDrawer *statusDrawer;

  static Gamebuff gb[StatusDrawer::CHARA_NUMBER];
  virtual void draw3D();
  virtual void draw2D();
  void lookatVector(Vector3f direction);

public:
  SceneMainGame() : BaseScene() {}
  SceneMainGame(WindowManager *window);
  SceneMainGame(WindowManager *window, ConfigData *config);

  virtual bool init();
  virtual SCENE_ID reactController(ControllerParam param);
  virtual SCENE_ID executeCommand(int command);
};