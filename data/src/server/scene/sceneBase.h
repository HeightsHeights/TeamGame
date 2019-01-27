#pragma once

/******************************************************************************
 * ベースシーン関係に必要なヘッダーの読み込み
******************************************************************************/
#include "../../common/network/networkCommand.h"
#include "../../common/scene/sceneId.h"
#include "../../common/math/vector/vectorSet.h"

#include "../data/clientData.h"

#define MAX_CLIENTS 2
/******************************************************************************
 * class BaseScene
 * 機能1：
 * 機能2：
******************************************************************************/

class BaseScene
{
private:
public:
  BaseScene() {}

  virtual bool init();
  virtual SCENE_ID executeCommand(int command, int pos);
  virtual SCENE_ID dataProcessing();

protected:
  static ClientData clientsData[MAX_CLIENTS];
};
