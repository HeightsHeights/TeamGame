#pragma once

/******************************************************************************
 * maingame関係に必要なヘッダーの読み込み
******************************************************************************/
#include "./sceneBase.h"
#include "../../common/gameData/teamStatus.h"
#include "../../common/gameData/clientNum.h"
#include "../data/gameObjectStatus.h"
#include "../data/charaStatus.h"
#include "./mainGame/itemSpawner.h"
#include "../../common/gameData/effectData.h"
#include "../../common/gameData/signalId.h"
/******************************************************************************
 * class SceneMainGame
 * 機能1：
 * 機能2：
******************************************************************************/

typedef enum
{
  PROGRESS_WAITING = 0,
  PROGRESS_GAMING = 1,
  PROGRESS_FINISHING = 2,
  PROGRESS_NUMBER = 3,
} GAME_PROGRESS;

class SceneMainGame : public BaseScene
{
private:
  unsigned int timer;
  GAME_PROGRESS progress;

  CharaStatus cStatus[MAX_PLAYERS];

  GameObjectStatus staticObjectStatus[SOBJECT_NUMBER];
  GameObjectStatus dynamicObjectStatus[MAX_DYNAMIC_OBJECTS];
  TeamStatus tStatus[TEAM_NUMBER];
  ItemSpawner itemSpawner;
  EffectData effects[MAX_EFFECT];

  bool gameInitable;

  SCENE_ID upDate();
  void sendData();
  void sendSignal(SIGNAL_ID signal);
  void sendResult(RESULT_ID resultData);
  void sendEffect(EFFECT_ID effect, Vector3f pos);

  void charaSpawningProcess(int id);
  void charaMovingProcess(int id);
  void charaGrabbingProcess(int id);
  void charaAttackingProcess(int id);

  void objectMovingProcess(int id);
  bool towerDamageProcess(int id, Collider collider, unsigned int damageValue);

  void buffProcess(int id);
  void setBuff(TEAM_ID teamId, BUFF_ID buffId);
  void resetBuff(TEAM_ID teamId, BUFF_ID buffId);

public:
  SceneMainGame() : BaseScene() {}

  virtual bool init();
  virtual SCENE_ID executeCommand(int command, int pos);
  virtual SCENE_ID dataProcessing();
};
