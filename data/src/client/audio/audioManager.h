
#pragma once
#include "./bgm.h"
#include "./se.h"
typedef enum {
  BGM_TITLE = 0,
  BGM_MAIN = 1,
  BGM_NUMBER = 2,
} BGM_ID;

typedef enum {
  SE_ATTACK = 0,
  SE_SODO = 1,
  SE_NUMBER = 2,
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
};
