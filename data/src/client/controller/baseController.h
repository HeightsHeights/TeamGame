#pragma once

#include <SDL2/SDL.h>
#include "../../common/controllerParam/controllerParam.h"

class BaseController
{
private:
  virtual void scanDirection(ControllerParam *param);
  virtual void scanButton(ControllerParam *param);

public:
  ~BaseController() {}
  virtual void cleanUp();
  virtual bool updateEvent();
  virtual bool scanEndFlag();
  ControllerParam readStateController();

protected:
  SDL_Event event;
};