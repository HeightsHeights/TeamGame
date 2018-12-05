#pragma once

/******************************************************************************
 * コントローラー関係に必要なヘッダーの読み込み
******************************************************************************/
#include "./baseController.h"
/******************************************************************************
 * class Joystick
 * 機能1：Joystickクラスを持つ
 * 機能2：コントローラー関係の初期化を行う
 * 機能3：コントローラーを更新してJoystickクラスから帰ってきたControllerParamをシーンに投げる
******************************************************************************/
class ControllerManager
{
private:
  static BaseController *controller;

public:
  static bool init();
  static bool updateController();
  static bool requestReaction(ControllerParam param);
  static void cleanUp();
#ifdef _ENABLE_WII
  static bool connectWiiRemote(const char *id);
#endif
};