#pragma once

/******************************************************************************
 * maingame関係に必要なヘッダーの読み込み
******************************************************************************/
#include "./sceneBase.h"
#include "../../common/gameData/teamStatus.h"
#include "../../common/gameData/clientNum.h"
#include "../data/gameObjectStatus.h"
#include "../data/charaStatus.h"

/******************************************************************************
 * class SceneMainGame
 * 機能1：
 * 機能2：
******************************************************************************/

class SceneMainGame : public BaseScene
{
private:
  unsigned int timer;

  CharaStatus cStatus[MAX_PLAYERS];

  GameObjectStatus staticObjectStatus[SOBJECT_NUMBER];
  GameObjectStatus dynamicObjectStatus[MAX_DYNAMIC_OBJECTS];

  TeamStatus tStatus[TEAM_NUMBER];

  bool gameInitable;

  void upDate();
  void sendData();

  void charaSpawningProcces(int id);
  void charaMovingProcces(int id);

public:
  SceneMainGame() : BaseScene() {}

  virtual bool init();
  virtual SCENE_ID executeCommand(int command, int pos);
  virtual SCENE_ID dataProcessing();
};
