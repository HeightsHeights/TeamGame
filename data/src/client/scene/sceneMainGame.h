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
  typedef enum {
    EFFECT_PUNCH = 1,
  } EFFECT_ID;

  ObjRawModel *tile;
  ObjRawModel *mush;

  Vector2f positionMush;
  Vector3f mushEye;
  GuiSprite *sprite;
  GuiSprite *eff;

  unsigned int effect_permission;

  StatusDrawer *statusDrawer;
  virtual void draw3D();
  virtual void draw2D();
  void lookatVector(Vector3f direction);
  void drawParticle();

public:
  SceneMainGame() : BaseScene() {}
  SceneMainGame(WindowManager *window);
  SceneMainGame(WindowManager *window, ConfigData *config);

  virtual bool init();
  virtual SCENE_ID reactController(ControllerParam param);
  virtual SCENE_ID executeCommand(int command);
};