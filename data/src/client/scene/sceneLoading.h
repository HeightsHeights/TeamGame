#pragma once

/******************************************************************************
 * title関係に必要なヘッダーの読み込み
******************************************************************************/
#include "./sceneBase.h"

#include "../../common/math/vector/vectorSet.h"
#include "../render/gui/image/guiImageLoader.h"
#include "../render/gui/text/guiTextLoader.h"
#include "../render/gui/sprite/guiSprite.h"
#include "../../common/math/ringCounter/ringCounter.h"

/******************************************************************************
 * class SceneTitle
 * 機能1：
 * 機能2：
******************************************************************************/

class SceneLoading : public BaseScene
{
public:
private:
  GuiImage *image[30];
  GuiImage *background;

  GuiText *loadingMessageText[4];

  RingCounter clockCounter;
  RingCounter loadingCounter;

  bool isFirst;
  virtual void draw3D();
  virtual void draw2D();

public:
  SceneLoading() : BaseScene() {}
  SceneLoading(WindowManager *window);
  SceneLoading(WindowManager *window, ConfigData *config);

  virtual bool init();
  virtual SCENE_ID reactController(ControllerParam param);
  virtual SCENE_ID executeCommand(int command);
};