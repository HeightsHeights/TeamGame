#pragma once

/******************************************************************************
 * chara関係に必要なヘッダーの読み込み
******************************************************************************/
#include "./sceneBase.h"
#include "../../common/math/vector/vectorSet.h"
#include "../network/networkManager.h"

/******************************************************************************
 * class SceneChara
 * 機能1：
 * 機能2：
******************************************************************************/

typedef struct
{
  Vector2f position;
} Player;

class SceneChara : public BaseScene
{
private:
  bool ready[MAX_CLIENTS];
  bool button[MAX_CLIENTS];
  static Player pl[MAX_CLIENTS];

public:
  SceneChara() : BaseScene() {}

  virtual bool init();
  virtual SCENE_ID executeCommand(int command, int pos);
};