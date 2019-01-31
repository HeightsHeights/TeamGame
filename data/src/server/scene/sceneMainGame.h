#pragma once

/******************************************************************************
 * maingame関係に必要なヘッダーの読み込み
******************************************************************************/
#include "./sceneBase.h"
#include "../../common/gameData/teamStatus.h"
#include "../gameObject/gameObject.h"
#include "../gameObject/character/character.h"

#include "../../common/gameData/clientNum.h"
#include "../../common/gameData/resultData.h"

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

  Character chara[MAX_PLAYERS];
  CharaStatus cStatus[MAX_PLAYERS];

  GameResult gResult[MAX_PLAYERS];

  Obb staticCollider[MAX_STATIC_OBJECTS];
  Obb CharaCollider[MAX_PLAYERS];

  // GameObject staticObject[MAX_STATIC_OBJECTS];
  // GameObject dynamicObject[MAX_DYNAMIC_OBJECTS];

  void upDate();
  void sendData();

public:
  SceneMainGame() : BaseScene() {}

  virtual bool init();
  virtual SCENE_ID executeCommand(int command, int pos);
  virtual SCENE_ID dataProcessing();
};
