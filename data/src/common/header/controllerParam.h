#pragma once

#define MAX_BUTTON 12
/******************************************************************************
 * コントローラーパラメーター関係に必要なヘッダーの読み込み
******************************************************************************/
#include "vector.h"

/******************************************************************************
 * class ControllerParam
 * Vector2f axisR/l：アナログスティックの軸を-1~1で保持する
 * bool buttonUp/Down：ボタンが押された瞬間（離された瞬間）にtrueになる
 * bool buttonState：ボタンが押されているときtrueそうでないときfalse
******************************************************************************/
class ControllerParam
{
  private:
  public:
    Vector2f axisR;
    Vector2f axisL;
    bool buttonUp[MAX_BUTTON];
    bool buttonDown[MAX_BUTTON];
    bool buttonState[MAX_BUTTON];
};