#pragma once

#include <SDL2/SDL.h>
#include "../../common/controllerParam/controllerParam.h"

class BaseController
{
private:

public:
  BaseController();
  virtual void updateEvent();
  virtual ControllerParam readStateController();

  protected:
    SDL_Event event;
};