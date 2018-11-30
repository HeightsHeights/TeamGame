#ifdef _ENABLE_WII

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

    bool isWiiUpdate = false;

    if (wiimote_is_open(&this->wiimote))
    {
        isWiiUpdate = wiimote_update(&wiimote);
    }
    return isSdlUpdate || isWiiUpdate;
}
WiiRemoteController *connect(const char *id)
{
    if (wiimote_connect(&wiimote, id) < 0)
    {
        return NULL;
    }
    wiimote.led.one = 1;
    return this;
}

#endif