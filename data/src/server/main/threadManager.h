#pragma once

#include <vector>
#include <SDL2/SDL.h>

class ThreadManager
{
private:
  static std::vector<SDL_Thread *> threads;
  static void *data;

public:
  static bool init(void *data);
  static bool start(SDL_ThreadFunction fp, const char *name);
  static int dataProcessingThread(void *data);
  static bool wait();
};