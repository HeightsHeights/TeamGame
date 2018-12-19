#pragma once

/******************************************************************************
 * rule関係に必要なヘッダーの読み込み
******************************************************************************/
#include "./sceneBase.h"
#include "../../common/math/vector/vectorSet.h"
/******************************************************************************
 * class SceneRule
 * 機能1：
 * 機能2：
******************************************************************************/

class SceneRule : public BaseScene
{
private:
  virtual void draw3D();
  virtual void draw2D();
  Vector2f position;

public:
  SceneRule() : BaseScene() {}
  SceneRule(WindowManager *window);

  virtual bool init();
  virtual SCENE_ID reactController(ControllerParam param);
  virtual SCENE_ID executeCommand(int command);
};