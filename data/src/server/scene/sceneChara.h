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
  bool button[MAX_PLAYERS];
  static Player pl[MAX_PLAYERS];

public:
  SceneChara() : BaseScene() {}

  virtual bool init();
  virtual SCENE_ID executeCommand(int command, int pos);
  virtual SCENE_ID dataProcessing();
};