#pragma once

#include "../../render/gui/image/guiImageLoader.h"
#include "../../render/gui/text/guiTextLoader.h"
#include "../../render/gui/sprite/guiSpriteLoader.h"

#define UNIT_WIDTH 50
class StatusDrawer
{
private:
  typedef enum {
    IMAGE_0 = 0,
    IMAGE_1 = 1,
    IMAGE_2 = 2,
    IMAGE_3 = 3,
    IMAGE_4 = 4,
    IMAGE_5 = 5,
    IMAGE_6 = 6,
    IMAGE_7 = 7,
    IMAGE_8 = 8,
    IMAGE_9 = 9,
    IMAGE_NAME_FRAME_RED = 10,
    IMAGE_NAME_FRAME_BLUE = 11,
    IMAGE_NAME_FRAME_YELLOW = 12,
    IMAGE_NAME_FRAME_GREEN = 13,
    IMAGE_ICON = 14,
    IMAGE_NUMBER = 15,
  } IMAGE_ID;

  GuiImage *image[IMAGE_NUMBER];

  void cleanUp();

public:
  typedef enum {
    COLOR_RED = 0,
    COLOR_BLUE = 1,
    COLOR_YELLOW = 2,
    COLOR_GREEN = 3,
    COLOR_NUMBER = 4,
  } COLOR_ID;

  StatusDrawer();
  ~StatusDrawer();

  bool init();
  void draw(Vector2f pos, COLOR_ID cid, unsigned int hp, bool alive, const char *name);
};