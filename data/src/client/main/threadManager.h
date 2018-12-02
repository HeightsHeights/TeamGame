#pragma once

#include <SDL2/SDL.h>

class ThreadManager
{
private:
public:
  static bool init(void *data);
  static int netWorkThread(void *data);
  static int controllerThread(void *data);
};