/******************************************************************************
 * コントローラー関係に必要なヘッダーの読み込み
******************************************************************************/

#include "./keybord.h"

/******************************************************************************
 * class Keybord
******************************************************************************/
void Keybord::scanDirection(ControllerParam *param)
{
}
void Keybord::scanButton(ControllerParam *param)
{
}

bool Keybord::updateEvent()
{
    return BaseController::updateEvent();
}