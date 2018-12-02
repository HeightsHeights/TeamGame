#pragma once

/******************************************************************************
 * ベースシーン関係に必要なヘッダーの読み込み
******************************************************************************/
#include "../render/window/window.h"
#include "./sceneId.h"
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
  virtual void reactController();
  virtual void executeCommand();
  virtual void drawWindow();

protected:
  WindowManager *window;
};