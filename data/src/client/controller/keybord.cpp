/******************************************************************************
 * コントローラー関係に必要なヘッダーの読み込み
******************************************************************************/

#include "./keybord.h"

/******************************************************************************
 * class Keybord
******************************************************************************/

void Keybord::scanDirection(ControllerParam *param)
{
    if (keys[SDLK_UP])
    {
        param->axisR.y = -1;
    }
    else if (keys[SDLK_DOWN])
    {
        param->axisR.y = 1;
    }
    else if (keys[SDLK_LEFT])
    {
        param->axisR.x = -1;
    }
    else if (keys[SDLK_LEFT])
    {
        param->axisR.x = 1;
    }
}

void Keybord::scanButton(ControllerParam *param)
{
    if (keys[SDLK_q])
    {
        param->buttonDown[0] = true;
        param->buttonUp[0] = false;
    }
    else
    {
        param->buttonDown[0] = false;
        param->buttonUp[0] = true;
    }

    if (keys[SDLK_w])
    {
        param->buttonDown[1] = true;
        param->buttonUp[1] = false;
    }
    else
    {
        param->buttonDown[1] = false;
        param->buttonUp[1] = true;
    }

    if (keys[SDLK_e])
    {
        param->buttonDown[2] = true;
        param->buttonUp[2] = false;
    }
    else
    {
        param->buttonDown[2] = false;
        param->buttonUp[2] = true;
    }

    if (keys[SDLK_r])
    {
        param->buttonDown[3] = true;
        param->buttonUp[3] = false;
    }
    else
    {
        param->buttonDown[3] = false;
        param->buttonUp[3] = true;
    }

    if (keys[SDLK_a])
    {
        param->buttonDown[4] = true;
        param->buttonUp[4] = false;
    }
    else
    {
        param->buttonDown[4] = false;
        param->buttonUp[4] = true;
    }

    if (keys[SDLK_s])
    {
        param->buttonDown[5] = true;
        param->buttonUp[5] = false;
    }
    else
    {
        param->buttonDown[5] = false;
        param->buttonUp[5] = true;
    }

    if (keys[SDLK_d])
    {
        param->buttonDown[6] = true;
        param->buttonUp[6] = false;
    }
    else
    {
        param->buttonDown[6] = false;
        param->buttonUp[6] = true;
    }

    if (keys[SDLK_f])
    {
        param->buttonDown[7] = true;
        param->buttonUp[7] = false;
    }
    else
    {
        param->buttonDown[7] = false;
        param->buttonUp[7] = true;
    }

    if (keys[SDLK_z])
    {
        param->buttonDown[8] = true;
        param->buttonUp[8] = false;
    }
    else
    {
        param->buttonDown[8] = false;
        param->buttonUp[8] = true;
    }

    if (keys[SDLK_x])
    {
        param->buttonDown[9] = true;
        param->buttonUp[9] = false;
    }
    else
    {
        param->buttonDown[9] = false;
        param->buttonUp[9] = true;
    }

    if (keys[SDLK_c])
    {
        param->buttonDown[10] = true;
        param->buttonUp[10] = false;
    }
    else
    {
        param->buttonDown[10] = false;
        param->buttonUp[10] = true;
    }

    if (keys[SDLK_v])
    {
        param->buttonDown[11] = true;
        param->buttonUp[11] = false;
    }
    else
    {
        param->buttonDown[11] = false;
        param->buttonUp[11] = true;
    }

    for (int i = 0; i > 12; i++)
    {
        if (param->buttonDown[i] = true)
        {
            param->buttonState[i] = true;
        }
        else
        {
            param->buttonState[i] = false;
        }
    }
}

void Keybord::updateEvent()
{
    BaseController::updateEvent();
}