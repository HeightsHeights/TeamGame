#pragma once

#define MAX_ANALOG_STICK_AXIS (float)32767
/******************************************************************************
 * コントローラー関係に必要なヘッダーの読み込み
******************************************************************************/
#include <SDL2/SDL.h>
#include "../../common/controllerParam/controllerParam.h"
#include "./baseController.h"
/******************************************************************************
 * class Joystick
 * 機能1：SDL_Joystickを保持する
 * 機能2：コンストラクタでSDL_Joystickを初期化
 * 機能3：SDL_Joystickを読み込んでControllerParamに変換して返す関数readStateControllerを持つ
******************************************************************************/
class Joystick : public BaseController
{
private:
  SDL_Joystick *joy;
  virtual void scanDirection(ControllerParam *param);
  virtual void scanButton(ControllerParam *param);

public:
  Joystick();
  Joystick(const unsigned int controllerID);
  virtual bool updateEvent();
  virtual bool scanEndFlag();
};