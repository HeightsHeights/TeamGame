#pragma once

/******************************************************************************
 * chara関係に必要なヘッダーの読み込み
******************************************************************************/
#include "./sceneBase.h"
#include "../render/objRawModel/objModelLoader.h"
#include "../../common/math/vector/vectorSet.h"
#include "../render/gui/image/guiImageLoader.h"
#include "../render/gui/text/guiTextLoader.h"
#define FRAME_WIDTH 80
#define MAX_LEN_NAME 256
#define MAX_PLAYER 2
typedef struct
{
  char subname[MAX_LEN_NAME];
  const char *name;
  Vector2f position;
} Player;
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
    IMAGE_PLAYER_FRAME_0 = 4,
    IMAGE_PLAYER_FRAME_1 = 5,
    IMAGE_PLAYER_FRAME_2 = 6,
    IMAGE_PLAYER_FRAME_3 = 7,
    IMAGE_NOTPLAYER_FRAME = 8,
    IMAGE_CHECK = 9,
    IMAGE_NUMBER = 10,
  } IMAGE_ID;

  typedef enum {
    COLOR_RED = 0,
    COLOR_BLUE = 1,
    COLOR_YELLOW = 2,
    COLOR_GREEN = 3,
    COLOR_NUMBER = 4,
  } COLOR_ID;
  virtual void drawBackground();
  virtual void draw3D();
  virtual void draw2D();
  Vector2f mypos;
  
  Vector2f positionChara;
  bool decision[MAX_PLAYER];
  bool connect[MAX_PLAYER];
  bool button;
  float bright;
  int count;
  static Player player[MAX_PLAYER];
  unsigned int angle;
  GuiImage *image[IMAGE_NUMBER];
  GuiRect dst[IMAGE_NUMBER];
  ObjRawModel *mush;
  ObjRawModel *bamboo;

  void drawPlayer(Vector2f pos, COLOR_ID cid, bool exit, bool ready, const char *name);

public:
  SceneChara() : BaseScene() {}
  SceneChara(WindowManager *window);
  SceneChara(WindowManager *window, ConfigData *config);

  virtual bool init();
  virtual SCENE_ID reactController(ControllerParam param);
  virtual SCENE_ID executeCommand(int command);
};