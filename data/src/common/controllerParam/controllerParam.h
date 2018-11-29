#pragma once

#define MAX_BUTTON 12
/******************************************************************************
 * コントローラーパラメーター関係に必要なヘッダーの読み込み
******************************************************************************/
#include "../math/vector/vector2f.h"

//ジョイコンの番号にあった番号を割り振ってください
typedef enum {
  CT_DECITION_OR_ATTACK = 1,
  CT_CANCEL = 4,
}ControllerTable;


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