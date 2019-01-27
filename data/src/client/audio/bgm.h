#pragma once
#include <SDL2/SDL_mixer.h>
class BGM
{
private:
  Mix_Music *bgm;

public:
  bool loadFile(const char *fileName);
  void play();
  void stop();
  void volume();
  void fadeIn(int ms);
  void fadeOut(int ms);
};
