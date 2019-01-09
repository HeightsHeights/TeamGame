#pragma once

/******************************************************************************
 * maingame関係に必要なヘッダーの読み込み
******************************************************************************/
#include "./sceneBase.h"

#include "../render/objRawModel/objModelLoader.h"

#include "../render/gui/image/guiImageLoader.h"
#include "../render/gui/text/guiTextLoader.h"
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

  GuiImage *imageNumber[10];

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