#ifdef USE_WII

/******************************************************************************
 * コントローラー関係に必要なヘッダーの読み込み
******************************************************************************/

#include "./wiiRemoteController.h"

/******************************************************************************
 * class Keybord
******************************************************************************/
void WiiRemoteController::scanDirection(ControllerParam *param)
{
}
void WiiRemoteController::scanButton(ControllerParam *param)
{
}

bool WiiRemoteController::updateEvent()
{
    bool isSdlUpdate = BaseController::updateEvent();

    bool isWiiUpdate = wiimote_update(&wiimote);

    return isSdlUpdate || isWiiUpdate;
}

#endif