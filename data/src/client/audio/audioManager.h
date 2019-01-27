
#pragma once
#include "./bgm.h"
#include "./se.h"
typedef enum {
  BGM_TITLE = 0,
  BGM_SELECT = 1,
  BGM_MAIN = 2,
  BGM_WIN = 3,
  BGM_LOSE = 4,
  BGM_NUMBER = 5,
} BGM_ID;

typedef enum {
  SE_DECISION = 0,
  SE_CURSOR = 1,
  SE_READY = 2,
  SE_BLOW = 3,
  SE_SOWORD = 4,
  SE_GUN = 5,
  SE_EXPLOSION = 6,
  SE_MISS = 7,
  SE_NUMBER = 8,
} SE_ID;

class AudioManager
{
private:
  static BGM bgm[BGM_NUMBER];
  static SE se[SE_NUMBER];

public:
  static bool init();
  static void playBGM(BGM_ID id);
  static void playSE(SE_ID id);
  static void stopBGM(BGM_ID id);
  static void stopSE(SE_ID id);
  static void volumeBGM(BGM_ID id);
  static void volumeSE(SE_ID id);
  static void fadeInBGM(BGM_ID id, int ms);
  static void fadeOutBGM(BGM_ID id, int ms);
};
