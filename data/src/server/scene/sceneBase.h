#pragma once

/******************************************************************************
 * ベースシーン関係に必要なヘッダーの読み込み
******************************************************************************/
#include "../../common/network/networkCommand.h"
#include "../../common/scene/sceneId.h"
#include "../../common/math/vector/vectorSet.h"

#define MAX_CLIENTS 2
/******************************************************************************
 * class BaseScene
 * 機能1：
 * 機能2：
******************************************************************************/
typedef enum {
  TEAM_MUSH = 0,
  TEAM_BAMBOO = 1,
  TEAM_NUMBER = 2,
} TEAM_ID;

typedef struct
{
  TEAM_ID tid;
  char name[256];
} GameData;

class BaseScene
{
private:
public:
  BaseScene() {}

  virtual bool init();
  virtual SCENE_ID executeCommand(int command, int pos);
  virtual SCENE_ID dataProcessing();

protected:
  static GameData gameData[MAX_CLIENTS];
};
