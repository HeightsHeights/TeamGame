#pragma once

/******************************************************************************
 * team関係に必要なヘッダーの読み込み
******************************************************************************/
#include "./sceneBase.h"
/******************************************************************************
 * class SceneTeam
 * 機能1：
 * 機能2：
******************************************************************************/

class SceneTeam : public BaseScene
{
private:
  virtual void draw3D();
  virtual void draw2D();

public:
  SceneTeam() : BaseScene() {}
  SceneTeam(WindowManager *window);

  virtual bool init();
  virtual SCENE_ID reactController(ControllerParam param);
  virtual SCENE_ID executeCommand(int command);
};