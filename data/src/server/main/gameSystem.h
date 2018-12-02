#pragma once

#include <SDL2/SDL.h>

class GameSystem
{
private:
  SDL_atomic_t atm;

public:
  bool init(int argc, char *argv[]);
  bool gameLoop();
  bool terminate();
};