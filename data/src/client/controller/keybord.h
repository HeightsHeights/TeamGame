#pragma once

#define MAX_ANALOG_STICK_AXIS (float)32767
/******************************************************************************
 * コントローラー関係に必要なヘッダーの読み込み
******************************************************************************/
#include "../../common/controllerParam/controllerParam.h"
#include "./baseController.h"
/******************************************************************************
 * class Keybord
******************************************************************************/
class Keybord : public BaseController
{
private:
  virtual void scanDirection(ControllerParam *param);
  virtual void scanButton(ControllerParam *param);
  const Uint8 *keys;

public:
  Keybord() { this->keys = SDL_GetKeyboardState(NULL); }
  virtual void cleanUp() {}
  virtual bool updateEvent();
  virtual bool scanEndFlag();
};