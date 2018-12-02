#pragma once

/******************************************************************************
 * title関係に必要なヘッダーの読み込み
******************************************************************************/
#include "./sceneBase.h"

#include "../render/objRawModel/objRawModel.h"
#include "../../common/math/vector/vectorSet.h"
/******************************************************************************
 * class SceneTitle
 * 機能1：
 * 機能2：
******************************************************************************/

class SceneTitle : public BaseScene
{
private:
  ObjRawModel *obj[2];
  Vector3f position[2];

public:
  SceneTitle() : BaseScene() {}
  SceneTitle(WindowManager *window);

  virtual bool init();
  virtual void reactController(ControllerParam param);
  virtual SCENE_ID executeCommand(int command);
  virtual void drawWindow();
};