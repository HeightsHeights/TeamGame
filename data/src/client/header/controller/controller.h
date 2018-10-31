#pragma once
/******************************************************************************
 * コントローラー関係に必要なヘッダーの読み込み
******************************************************************************/
#include <SDL2/SDL.h>
#include "../../../common/header/controllerParam.h"
/******************************************************************************
 * class Joystick
 * 機能1：SDL_Joystickを保持する
 * 機能2：コンストラクタでSDL_Joystickを初期化
 * 機能3：SDL_Joystickを読み込んでControllerParamに変換して返す関数readStateControllerを持つ
******************************************************************************/
class Joystick
{
  private:
    SDL_Joystick *joystick;

  public:
    Joystick(const unsigned int controllerID);
    ControllerParam readStateController();
};
/******************************************************************************
 * class Joystick
 * 機能1：Joystickクラスを持つ
 * 機能2：コントローラー関係の初期化を行う
 * 機能3：コントローラーを更新してJoystickクラスから帰ってきたControllerParamをシーンに投げる
******************************************************************************/
class ControllerManager
{
  private:
  public:
    static bool init();
    static int updateController();
    static void requestReaction();
    static void cleanUp();
};