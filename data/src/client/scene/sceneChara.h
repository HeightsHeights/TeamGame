#pragma once

/******************************************************************************
 * chara関係に必要なヘッダーの読み込み
******************************************************************************/
#include "./sceneBase.h"
#include "../../common/math/vector/vectorSet.h"
/******************************************************************************
 * class SceneChara
 * 機能1：
 * 機能2：
******************************************************************************/

class SceneChara : public BaseScene
{
private:
  virtual void draw3D();
  virtual void draw2D();
  Vector3f position;
public:
  SceneChara() : BaseScene() {}
  SceneChara(WindowManager *window);

  virtual bool init();
  virtual SCENE_ID reactController(ControllerParam param);
  virtual SCENE_ID executeCommand(int command);
};