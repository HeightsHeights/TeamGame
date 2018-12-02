/******************************************************************************
 * コントローラー関係に必要なヘッダーの読み込み
******************************************************************************/

#include "./keybord.h"

/******************************************************************************
 * class Keybord
******************************************************************************/

void Keybord::scanDirection(ControllerParam *param)
{
    if (keys[SDLK_w])
    {
        param->axisL.y = -1;
    }
    else if (keys[SDLK_s])
    {
        param->axisL.y = 1;
    }
    else if (keys[SDLK_a])
    {
        param->axisL.x = -1;
    }
    else if (keys[SDLK_d])
    {
        param->axisL.x = 1;
    }

    if (keys[SDLK_8])
    {
        param->axisR.y = -1;
    }
    else if (keys[SDLK_2])
    {
        param->axisR.y = 1;
    }
    else if (keys[SDLK_4])
    {
        param->axisR.x = -1;
    }
    else if (keys[SDLK_6])
    {
        param->axisR.x = 1;
    }
}

void Keybord::scanButton(ControllerParam *param)
{
    if (keys[SDLK_p])
    {
        param->buttonDown[CT_DECITION_OR_ATTACK] = true;
        param->buttonUp[CT_DECITION_OR_ATTACK] = false;
    }
    else
    {
        param->buttonDown[CT_DECITION_OR_ATTACK] = false;
        param->buttonUp[CT_DECITION_OR_ATTACK] = true;
    }

    if (keys[SDLK_i])
    {
        param->buttonDown[CT_GUARD] = true;
        param->buttonUp[CT_GUARD] = false;
    }
    else
    {
        param->buttonDown[CT_GUARD] = false;
        param->buttonUp[CT_GUARD] = true;
    }

    if (keys[SDLK_u])
    {
        param->buttonDown[CT_GRUB] = true;
        param->buttonUp[CT_GRUB] = false;
    }
    else
    {
        param->buttonDown[CT_GRUB] = false;
        param->buttonUp[CT_GRUB] = true;
    }

    if (keys[SDLK_5])
    {
        param->buttonDown[CT_PRDGDIRECTION] = true;
        param->buttonUp[CT_PRDGDIRECTION] = false;
    }
    else
    {
        param->buttonDown[CT_PRDGDIRECTION] = false;
        param->buttonUp[CT_PRDGDIRECTION] = true;
    }

    if (keys[SDLK_SPACE])
    {
        param->buttonDown[CT_PAUSE] = true;
        param->buttonUp[CT_PAUSE] = false;
    }
    else
    {
        param->buttonDown[CT_PAUSE] = false;
        param->buttonUp[CT_PAUSE] = true;
    }

    if (keys[SDLK_BACKSPACE])
    {
        param->buttonDown[CT_CANCEL] = true;
        param->buttonUp[CT_CANCEL] = false;
    }
    else
    {
        param->buttonDown[CT_CANCEL] = false;
        param->buttonUp[CT_CANCEL] = true;
    }

    if (keys[SDLK_q] || keys[SDLK_e])
    {
        param->buttonDown[CT_JUMP] = true;
        param->buttonUp[CT_JUMP] = false;
    }
    else
    {
        param->buttonDown[CT_JUMP] = false;
        param->buttonUp[CT_JUMP] = true;
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

bool Keybord::updateEvent()
{
    return BaseController::updateEvent();
    keys = SDL_GetKeyboardState(NULL);
}

bool Keybord::scanEndFrag()
{
    if (BaseController::scanEndFrag())
    {
        return true;
    }
    if (event.key.keysym.sym == SDLK_ESCAPE)
    {
        return true;
    }
    return false;
}
