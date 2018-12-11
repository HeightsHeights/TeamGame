
#pragma once
#include "./bgm.h"
#include "./se.h"
typedef enum {
  BGM_TITLE = 0,
  BGM_NUMBER = 1,
} BGM_ID;

typedef enum {
  SE_NULL = 0,
  SE_SODO = 1,
  SE_HAMMER = 2,
  SE_NUMBER = 3,
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
