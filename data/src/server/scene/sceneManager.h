#pragma once

typedef enum
{
  SI_TITLE = 0,
  SI_MAIN = 1,
  SI_NUMBER = 2,
} SCENE_ID;
/******************************************************************************
 * SceneManager関係に必要なヘッダーの読み込み
******************************************************************************/
#include "./sceneBase.h"
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
  static void executeCommand();
};