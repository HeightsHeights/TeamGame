
#pragma once
#include "./bgm.h"
#include "./se.h"
typedef enum {
  BGM_TITLE = 0,
  BGM_MAIN = 1,
  BGM_NUMBER = 2,
} BGM_ID;

typedef enum {
  SE_SODO = 0,
  SE_HAMMER = 1,
  SE_NUMBER = 2,
} SE_ID;

class AudioManager
{
private:
  BGM bgm[BGM_NUMBER];
  SE se[SE_NUMBER];

public:
  static bool init();
  static void playBGM(BGM_ID id);
  static void playSE(SE_ID id);
  static void stopBGM(BGM_ID id);
  static void stopSE(SE_ID id);
};
