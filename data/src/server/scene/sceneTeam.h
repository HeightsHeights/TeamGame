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
  Vector2f position[2];
  bool button[2];
public:
  SceneTeam() : BaseScene() {}

  virtual bool init();
  virtual SCENE_ID executeCommand(int command, int pos);
};