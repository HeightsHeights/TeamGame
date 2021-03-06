#pragma once

#include "../../../common//gameData/resultId.h"
#include "../../render/gui/image/guiImageLoader.h"
#include "../../render/gui/text/guiTextLoader.h"
#include "../../render/gui/sprite/guiSpriteLoader.h"
#include "../../../common/gameData/teamStatus.h"
#include "../../../common/gameData/teamId.h"
#include "../../../common/gameData/signalId.h"

#define UNIT_WIDTH 50
#define HP_WIDTH 400

class StatusDrawer
{
private:
  typedef enum
  {
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
    IMAGE_READY = 19,
    IMAGE_GO = 20,
    IMAGE_FINISH = 21,
    IMAGE_WINNER = 22,
    IMAGE_MUSH_WIN = 23,
    IMAGE_BAMBOO_WIN = 24,
    IMAGE_YOU_ARE_DEAD = 25,
    IMAGE_NUMBER = 26,
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
  void drawDeadMessage(float size, unsigned int spawningTime);
  void drawReadySignal(SIGNAL_ID id, Vector2f pos);
};