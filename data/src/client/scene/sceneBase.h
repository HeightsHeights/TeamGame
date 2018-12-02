#pragma once

/******************************************************************************
 * ベースシーン関係に必要なヘッダーの読み込み
******************************************************************************/
#include "../render/window/window.h"
#include "./sceneId.h"
#include "../../common/controllerParam/controllerParam.h"
/******************************************************************************
 * class BaseScene
 * 機能1：
 * 機能2：
******************************************************************************/

class BaseScene
{
private:
public:
  BaseScene();
  BaseScene(WindowManager *window);

  virtual bool init();
  virtual void reactController(ControllerParam param);
  virtual SCENE_ID executeCommand(int command);
  virtual void drawWindow();

protected:
  WindowManager *window;
};