#pragma once

/******************************************************************************
 * title関係に必要なヘッダーの読み込み
******************************************************************************/
#include "./sceneBase.h"
#include "../../common/math/vector/vectorSet.h"
/******************************************************************************
 * class SceneTitle
 * 機能1：
 * 機能2：
******************************************************************************/

class SceneLoading : public BaseScene
{
private:
  int numRecieveName;

public:
  SceneLoading() : BaseScene() {}

  virtual bool init();
  virtual SCENE_ID executeCommand(int command, int pos);
  virtual SCENE_ID dataProcessing();
};