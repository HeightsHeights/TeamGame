#pragma once

/******************************************************************************
 * maingame関係に必要なヘッダーの読み込み
******************************************************************************/
#include "./sceneBase.h"
#include "../../common/gameData/teamStatus.h"

#include "../../common/gameData/clientNum.h"

#include "../data/gameObjectStatus.h"
#include "../data/charaStatus.h"

#define MAX_STATIC_OBJECTS 8
#define MAX_DYNAMIC_OBJECTS 100

/******************************************************************************
 * class SceneMainGame
 * 機能1：
 * 機能2：
******************************************************************************/

class SceneMainGame : public BaseScene
{
private:
  unsigned int timer;

  TeamStatus tStatus[TEAM_NUMBER];

  void upDate();
  void sendData();

public:
  SceneMainGame() : BaseScene() {}

  virtual bool init();
  virtual SCENE_ID executeCommand(int command, int pos);
  virtual SCENE_ID dataProcessing();
};
