#ifdef _ENABLE_WII

/******************************************************************************
 * コントローラー関係に必要なヘッダーの読み込み
******************************************************************************/

#include "./wiiRemote.h"

/******************************************************************************
 * class Keybord
******************************************************************************/
void WiiRemote::scanDirection(ControllerParam *param)
{
    param->axisL = Vector2f_ZERO;
    param->axisR = Vector2f_ZERO;
    if (wiimote.keys.up)
    {
        param->axisR.y += -1;
    }
    if (wiimote.keys.down)
    {
        param->axisR.y += 1;
    }
    if (wiimote.keys.left)
    {
        param->axisR.x += -1;
    }
    if (wiimote.keys.right)
    {
        param->axisR.x += 1;
    }

    if (wiimote.ext.nunchuk.joyy < 93)
    {
        param->axisL.y = 1;
    }
    else if (wiimote.ext.nunchuk.joyy > 153)
    {
        param->axisL.y = -1;
    }
    if (wiimote.ext.nunchuk.joyx < 93)
    {
        param->axisL.x = -1;
    }
    else if (wiimote.ext.nunchuk.joyx > 153)
    {
        param->axisL.x = 1;
    }
}

void WiiRemote::scanButton(ControllerParam *param)
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

bool WiiRemote::updateEvent()
{
    bool isSdlUpdate = BaseController::updateEvent();

    bool isWiiUpdate = false;

    if (wiimote_is_open(&this->wiimote))
    {
        isWiiUpdate = wiimote_update(&this->wiimote);
    }
    return isSdlUpdate || isWiiUpdate;
}

bool WiiRemote::scanEndFlag()
{
    if (BaseController::scanEndFlag())
    {
        return true;
    }
    if (wiimote.keys.a && wiimote.keys.b && wiimote.ext.nunchuk.keys.c && wiimote.ext.nunchuk.keys.c)
    {
        return true;
    }
    return false;
}

#endif