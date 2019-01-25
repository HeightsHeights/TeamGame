#pragma once

/******************************************************************************
 * title関係に必要なヘッダーの読み込み
******************************************************************************/
#include "./sceneBase.h"

#include "../../common/math/vector/vectorSet.h"
#include "../render/gui/image/guiImageLoader.h"
#include "../render/gui/text/guiTextLoader.h"

/******************************************************************************
 * class SceneTitle
 * 機能1：
 * 機能2：
******************************************************************************/

class SceneLoading : public BaseScene
{
public:
private:
  typedef enum {
    ANIME_0 = 0,
    ANIME_1 = 1,
    ANIME_2 = 2,
    ANIME_3 = 3,
    ANIME_4 = 4,
    ANIME_5 = 5,
    ANIME_6 = 6,
    ANIME_7 = 7,
    ANIME_NUMBER = 8,
  } ANIME_ID;
  int count;
  GuiImage *image[ANIME_NUMBER];
  virtual void draw3D();
  virtual void draw2D();

public:
  SceneLoading() : BaseScene() {}
  SceneLoading(WindowManager *window);
  SceneLoading(WindowManager *window, ConfigData *config);

  virtual bool init();
  virtual SCENE_ID reactController(ControllerParam param);
  virtual SCENE_ID executeCommand(int command);
};