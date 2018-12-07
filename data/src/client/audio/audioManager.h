#include "./baseSound.h"

typedef enum{
    AID_STATIC = 0,
    AID_TEST = 1,
    AID_NUM = 2,
}Sound_ID;

class AudioManager{
  private:
    static BaseSound *audio[AID_NUM];
  public:
    static bool initAudio();
    static void playAudio(Sound_ID aid);
    static void stopAudio(Sound_ID aid);

};
