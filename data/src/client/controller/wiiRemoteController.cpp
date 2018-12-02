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
    if (wiimote.keys.up)
    {
        param->axisR.y = -1;
    }
    else if (wiimote.keys.down)
    {
        param->axisR.y = 1;
    }
    else if (wiimote.keys.left)
    {
        param->axisR.x = -1;
    }
    else if (wiimote.keys.right)
    {
        param->axisR.x = 1;
    }
}
void WiiRemoteController::scanButton(ControllerParam *param)
{
    if (wiimote.keys.a)
    {
        param->buttonDown[CT_DECITION_OR_ATTACK] = true;
        param->buttonUp[CT_DECITION_OR_ATTACK] = false;
    }
    else
    {
        param->buttonDown[CT_DECITION_OR_ATTACK] = false;
        param->buttonUp[CT_DECITION_OR_ATTACK] = true;
    }

    if (wiimote.ext.nunchuk.keys.z)
    {
        param->buttonDown[CT_GUARD] = true;
        param->buttonUp[CT_GUARD] = false;
    }
    else
    {
        param->buttonDown[CT_GUARD] = false;
        param->buttonUp[CT_GUARD] = true;
    }

    if (wiimote.keys.plus)
    {
        param->buttonDown[CT_GRUB] = true;
        param->buttonUp[CT_GRUB] = false;
    }
    else
    {
        param->buttonDown[CT_GRUB] = false;
        param->buttonUp[CT_GRUB] = true;
    }

    if (wiimote.keys.home)
    {
        param->buttonDown[CT_PAUSE] = true;
        param->buttonUp[CT_PAUSE] = false;
    }
    else
    {
        param->buttonDown[CT_PAUSE] = false;
        param->buttonUp[CT_PAUSE] = true;
    }

    if (wiimote.keys.one)
    {
        param->buttonDown[CT_CANCEL] = true;
        param->buttonUp[CT_CANCEL] = false;
    }
    else
    {
        param->buttonDown[CT_CANCEL] = false;
        param->buttonUp[CT_CANCEL] = true;
    }

    if (wiimote.ext.nunchuk.keys.c)
    {
        param->buttonDown[CT_PRDGDIRECTION] = true;
        param->buttonUp[CT_PRDGDIRECTION] = false;
    }
    else
    {
        param->buttonDown[CT_PRDGDIRECTION] = false;
        param->buttonUp[CT_PRDGDIRECTION] = true;
    }
}

bool WiiRemoteController::updateEvent()
{
    bool isSdlUpdate = BaseController::updateEvent();

    bool isWiiUpdate = false;

    if (wiimote_is_open(&this->wiimote))
    {
        isWiiUpdate = wiimote_update(&this->wiimote);
    }
    return isSdlUpdate || isWiiUpdate;
}

WiiRemoteController *WiiRemoteController::connect(const char *id)
{
    if (wiimote_connect(&this->wiimote, id) < 0)
    {
        return NULL;
    }
    wiimote.led.one = 1;
    return this;
}

bool Joystick::scanEndFlag()
{
    if (BaseController::scanEndFlag())
    {
        return true;
    }
    return false;
}

#endif