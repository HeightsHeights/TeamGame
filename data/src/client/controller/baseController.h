#pragma once

#include <SDL2/SDL.h>
#include "../../common/controllerParam/controllerParam.h"

class BaseController
{
private:
  virtual void scanDirection(ControllerParam *param);
  virtual void scanButton(ControllerParam *param);

public:
  virtual bool updateEvent();
  ControllerParam readStateController();

protected:
  SDL_Event event;
};