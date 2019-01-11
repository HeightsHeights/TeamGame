#pragma once

/******************************************************************************
 * title関係に必要なヘッダーの読み込み
******************************************************************************/
#include "./sceneBase.h"

#include "../render/objRawModel/objModelLoader.h"
#include "../render/xLoader/xLoader.h"
#include "../../common/math/vector/vectorSet.h"
#include "../render/gui/image/guiImageLoader.h"
#include "../render/gui/text/guiTextLoader.h"

/******************************************************************************
 * class SceneTitle
 * 機能1：
 * 機能2：
******************************************************************************/

class SceneTitle : public BaseScene
{
public:
  typedef enum {
    IMAGE_TITLE = 0,
    IMAGE_BG = 1,
    IMAGE_START = 2,
    IMAGE_CONFIG = 3,
    IMAGE_END = 4,
    IMAGE_SAVE = 5,
    IMAGE_CANCEL = 6,
    IMAGE_RESET = 7,
    IMAGE_CONFIG_FRAME_0 = 8,
    IMAGE_CONFIG_FRAME_1 = 9,
    IMAGE_CONFIG_FRAME_2 = 10,
    IMAGE_NUMBER = 11,
  } IMAGE_ID;

  typedef enum {
    TEXT_SAVE = 0,
    TEXT_CANCEL = 1,
    TEXT_RESET = 2,
    TEXT_NUMBER = 3,
  } TEXT_ID;

private:
  Vector2f configPos;
  Vector2f position[2];
  bool button;
  bool configmode;
  GuiText *text[TEXT_NUMBER];
  GuiImage *image[IMAGE_NUMBER];
  int num;
  int secount;
  float bright;
  ConfigData *subconfig;
  GuiRect dst[IMAGE_NUMBER];
  GuiRect dst2[TEXT_NUMBER];
  virtual void draw3D();
  virtual void draw2D();

  void drawConfig(Vector2f pos);
  void drawConfigElement(Vector2f pos, std::string label, std::string string, bool selected);

public:
  SceneTitle() : BaseScene() {}
  SceneTitle(WindowManager *window);
  SceneTitle(WindowManager *window, ConfigData *config);

  virtual bool init();
  virtual SCENE_ID reactController(ControllerParam param);
  virtual SCENE_ID executeCommand(int command);
};