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
public:
  SceneTeam() : BaseScene() {}

  virtual bool init();
  virtual SCENE_ID executeCommand(int command, int pos);
};