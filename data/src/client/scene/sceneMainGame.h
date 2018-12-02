#pragma once

/******************************************************************************
 * maingame関係に必要なヘッダーの読み込み
******************************************************************************/
#include "./sceneBase.h"
/******************************************************************************
 * class SceneMainGame
 * 機能1：
 * 機能2：
******************************************************************************/

class SceneMainGame : public BaseScene
{
private:
public:
  SceneMainGame() : BaseScene() {}
  SceneMainGame(WindowManager *window);

  virtual bool init();
  virtual void reactController();
  virtual void executeCommand();
  virtual void drawWindow();
};