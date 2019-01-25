#pragma once

/******************************************************************************
 * ベースシーン関係に必要なヘッダーの読み込み
******************************************************************************/
#include "../render/window/window.h"
#include "../../common/scene/sceneId.h"
#include "../../common/controllerParam/controllerParam.h"
#include "../config/configData.h"

#define MAX_PLAYER 2
/******************************************************************************
 * class BaseScene
 * 機能1：
 * 機能2：
******************************************************************************/

class BaseScene
{
private:
  WindowManager *window;
  virtual void drawBackground();
  virtual void draw3D();
  virtual void draw2D();

public:
  BaseScene();
  BaseScene(WindowManager *window);
  BaseScene(WindowManager *window, ConfigData *config);

  virtual bool init();
  virtual SCENE_ID reactController(ControllerParam param);
  virtual SCENE_ID executeCommand(int command);
  void drawWindow();

protected:
  ConfigData *config;
};