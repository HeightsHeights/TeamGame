#pragma once

/******************************************************************************
 * SceneManager関係に必要なヘッダーの読み込み
******************************************************************************/
#include "./sceneBase.h"
#include "../../common/scene/sceneId.h"
/******************************************************************************
 * class SceneManager
 * 機能1：
 * 機能2：
******************************************************************************/
class SceneManager
{
private:
  static int sceneId;
  static BaseScene *scenes[SI_NUMBER];

public:
  static bool init();
  static bool executeCommand(int command, int pos);
};