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

typedef enum {
  IMAGE_TITLE = 0,
  IMAGE_BG = 1,
  IMAGE_NUMBER = 2,
} IMAGE_ID;

typedef enum {
  TEXT_START = 0,
  TEXT_CONFIG = 1,
  TEXT_END = 2,
  TEXT_YOUSERNAME = 3,
  TEXT_SERVERID = 4,
  TEXT_WIIMOTEID = 5,
  TEXT_SAVE = 6,
  TEXT_CANCEL = 7,
  TEXT_RESET = 8,
  TEXT_NUMBER = 9,
} TEXT_ID;
/******************************************************************************
 * class SceneTitle
 * 機能1：
 * 機能2：
******************************************************************************/

class SceneTitle : public BaseScene
{
private:
  // GLuint vao1;
  // GLuint vao2;
  // GLuint texId;
  // ObjRawModel *obj;
  // XModel *model;
  //float angle;
  Vector2f position[2];
  bool button;
  bool configmode;
  GuiText *text[TEXT_NUMBER];
  GuiImage *image[IMAGE_NUMBER];
  int num;

  virtual void draw3D();
  virtual void draw2D();

public:
  SceneTitle() : BaseScene() {}
  SceneTitle(WindowManager *window);
  SceneTitle(WindowManager *window, ConfigData *config);

  virtual bool init();
  virtual SCENE_ID reactController(ControllerParam param);
  virtual SCENE_ID executeCommand(int command);
};