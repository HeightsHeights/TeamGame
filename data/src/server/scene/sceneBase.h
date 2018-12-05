#pragma once

/******************************************************************************
 * ベースシーン関係に必要なヘッダーの読み込み
******************************************************************************/
#include "../../common/network/networkCommand.h"
#include "../../common/scene/sceneId.h"
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

protected:
};