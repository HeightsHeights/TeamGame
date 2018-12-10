#pragma once
#include <SDL2/SDL_mixer.h>
class SE
{
  private:
    Mix_Chunk *se;

  public:
    bool loadFile(const char *fileName);
    void play();
    void stop();
};