#pragma once

/******************************************************************************
 * title関係に必要なヘッダーの読み込み
******************************************************************************/
#include "./sceneBase.h"

#include "../render/objRawModel/objModelLoader.h"
#include "../render/xLoader/xLoader.h"
#include "../../common/math/vector/vectorSet.h"
/******************************************************************************
 * class SceneTitle
 * 機能1：
 * 機能2：
******************************************************************************/

class SceneTitle : public BaseScene
{
private:
  GLuint vao1;
  GLuint vao2;
  GLuint texId;
  ObjRawModel *obj;
  XModel *model;
  float angle;

public:
  SceneTitle() : BaseScene() {}
  SceneTitle(WindowManager *window);

  virtual bool init();
  virtual SCENE_ID reactController(ControllerParam param);
  virtual SCENE_ID executeCommand(int command);
  virtual void drawWindow();
};