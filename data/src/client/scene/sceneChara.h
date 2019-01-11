#pragma once

/******************************************************************************
 * chara関係に必要なヘッダーの読み込み
******************************************************************************/
#include "./sceneBase.h"
#include "../render/objRawModel/objModelLoader.h"
#include "../../common/math/vector/vectorSet.h"
#include "../render/gui/image/guiImageLoader.h"
#include "../render/gui/text/guiTextLoader.h"
/******************************************************************************
 * class SceneChara
 * 機能1：
 * 機能2：
******************************************************************************/

class SceneChara : public BaseScene
{
private:
  typedef enum {
    IMAGE_CONFIGBG = 0,
    IMAGE_BAMBOO = 1,
    IMAGE_MUSHROOM = 2,
    IMAGE_READY = 3,
    IMAGE_NUMBER = 4,
  } IMAGE_ID;

  virtual void draw3D();
  virtual void draw2D();
  Vector2f position;
  bool decision[4];
  bool connect[4];
  bool button;
  int playernum;
  float bright;

  GuiImage *image[IMAGE_NUMBER];
  GuiRect dst[IMAGE_NUMBER];

public:
  SceneChara() : BaseScene() {}
  SceneChara(WindowManager *window);
  SceneChara(WindowManager *window, ConfigData *config);

  virtual bool init();
  virtual SCENE_ID reactController(ControllerParam param);
  virtual SCENE_ID executeCommand(int command);
};