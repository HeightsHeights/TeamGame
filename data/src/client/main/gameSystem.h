#pragma once

#include "../render/window/window.h"
#include "../config/configData.h"

class GameSystem
{
private:
  ConfigData *config;
  WindowManager *window;
  SDL_atomic_t atm;

  bool loadConfig(std::string fileName);
  bool saveConfig(std::string fileName);
  bool makeWindow(int argc, char *argv[], std::string windowName);

public:
  bool init(int argc, char *argv[]);
  bool gameLoop();
  bool terminate();
};