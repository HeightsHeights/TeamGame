#pragma once

/******************************************************************************
 * chara関係に必要なヘッダーの読み込み
******************************************************************************/
#include "./sceneBase.h"
#include "../../common/math/vector/vectorSet.h"
#include "../network/networkManager.h"

#define MAX_PLAYER 2
/******************************************************************************
 * class SceneChara
 * 機能1：
 * 機能2：
******************************************************************************/

class SceneChara : public BaseScene
{
private:
  bool ready[MAX_PLAYER];
  bool button[MAX_PLAYER];
  Vector2f position;
  static Client player[MAX_CLIENTS];
public:
  SceneChara() : BaseScene() {}

  virtual bool init();
  virtual SCENE_ID executeCommand(int command, int pos);
};