#pragma once

#include "../../../common//gameData/resultData.h"
#include "../../render/gui/image/guiImageLoader.h"
#include "../../render/gui/text/guiTextLoader.h"
#include "../../render/gui/sprite/guiSpriteLoader.h"
#include "../../../common/gameData/teamStatus.h"
#include "../../../common/gameData/teamData.h"

#define UNIT_WIDTH 50
#define HP_WIDTH 400

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
    IMAGE_NAME_FRAME_MUSH = 10,
    IMAGE_NAME_FRAME_BAMBOO = 11,
    IMAGE_HP = 12,
    IMAGE_HPBACK = 13,
    IMAGE_ATKBUFF = 14,
    IMAGE_HPBUFF = 15,
    IMAGE_SPBUFF = 16,
    IMAGE_MUSHHPFRAME = 17,
    IMAGE_BAMBOOHPFRAME = 18,
    IMAGE_WIN = 19,
    IMAGE_LOSE = 20,
    IMAGE_NUMBER = 21,
  } IMAGE_ID;
  GuiImage *image[IMAGE_NUMBER];

  void cleanUp();

public:
  StatusDrawer();
  ~StatusDrawer();

  bool init();
  void draw(Vector2f pos, TEAM_ID id, unsigned int hp, bool alive, const char *name);
  void drawTeamStatus(Vector2f pos, TEAM_ID id, TeamStatus status);
  void drawTeamStatus(Vector2f pos, TEAM_ID id, TeamStatus status, Vector3f loc);
  void drawResult(RESULT_ID result);
};