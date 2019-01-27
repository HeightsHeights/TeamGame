#pragma once

/******************************************************************************
 * maingame関係に必要なヘッダーの読み込み
******************************************************************************/
#include "./sceneBase.h"
#include "../../common/gameData/teamStatus.h"
#include "../gameObject/gameObject.h"
#include "../gameObject/character/character.h"

#define MAX_STATIC_OBJECTS 20
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

  TeamStatus status[TEAM_NUMBER];

  Character chara[MAX_CLIENTS];
  GameObject staticObject[MAX_STATIC_OBJECTS];
  GameObject dynamicObject[MAX_DYNAMIC_OBJECTS];

public:
  SceneMainGame() : BaseScene()
  {
  }

  virtual bool init();
  virtual SCENE_ID executeCommand(int command, int pos);
  virtual SCENE_ID dataProcessing();
};

//