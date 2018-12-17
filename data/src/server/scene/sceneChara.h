#pragma once

/******************************************************************************
 * chara関係に必要なヘッダーの読み込み
******************************************************************************/
#include "./sceneBase.h"
/******************************************************************************
 * class SceneChara
 * 機能1：
 * 機能2：
******************************************************************************/

class SceneChara : public BaseScene
{
private:
public:
  SceneChara() : BaseScene() {}

  virtual bool init();
  virtual SCENE_ID executeCommand(int command, int pos);
};