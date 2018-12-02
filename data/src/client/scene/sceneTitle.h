#pragma once

/******************************************************************************
 * title関係に必要なヘッダーの読み込み
******************************************************************************/
#include "./sceneBase.h"

#include "../render/objRawModel/objRawModel.h"
/******************************************************************************
 * class SceneTitle
 * 機能1：
 * 機能2：
******************************************************************************/

class SceneTitle : public BaseScene
{
private:
  ObjRawModel *obj;

public:
  SceneTitle() : BaseScene() {}
  SceneTitle(WindowManager *window);

  virtual bool init();
  virtual void reactController();
  virtual SCENE_ID executeCommand();
  virtual void drawWindow();
};