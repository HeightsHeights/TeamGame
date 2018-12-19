#pragma once

/******************************************************************************
 * team関係に必要なヘッダーの読み込み
******************************************************************************/
#include "./sceneBase.h"
#include "../../common/math/vector/vectorSet.h"
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
  Vector2f position[2];

public:
  SceneTeam() : BaseScene() {}
  SceneTeam(WindowManager *window);

  virtual bool init();
  virtual SCENE_ID reactController(ControllerParam param);
  virtual SCENE_ID executeCommand(int command);
};