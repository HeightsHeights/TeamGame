#pragma once

#include <SDL2/SDL.h>

class ThreadManager
{
private:
  static SDL_Thread *cThread;
  static SDL_Thread *nThread;

public:
  static bool init(void *data);
  static int netWorkThread(void *data);
  static int controllerThread(void *data);
  static bool wait();
};