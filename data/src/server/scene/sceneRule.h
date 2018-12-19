#pragma once

/******************************************************************************
 * rule関係に必要なヘッダーの読み込み
******************************************************************************/
#include "./sceneBase.h"
#include "../../common/scene/sceneParam.h"
#include "../../common/math/vector/vectorSet.h"
/******************************************************************************
 * class SceneRule
 * 機能1：
 * 機能2：
******************************************************************************/

class SceneRule : public BaseScene
{
private:
  Vector2f position;
  SceneParam param;

public:
  SceneRule() : BaseScene() {}

  virtual bool init();
  virtual SCENE_ID executeCommand(int command, int pos);
};