/******************************************************************************
 * コントローラー関係に必要なヘッダーの読み込み
******************************************************************************/

#include "./keybord.h"

/******************************************************************************
 * class Keybord
******************************************************************************/

void Keybord::scanDirection(ControllerParam *param)
{
    if (keys[SDL_SCANCODE_W])
    {
        param->axisL.y += -1;
    }
    if (keys[SDL_SCANCODE_S])
    {
        param->axisL.y += 1;
    }
    if (keys[SDL_SCANCODE_A])
    {
        param->axisL.x += -1;
    }
    if (keys[SDL_SCANCODE_D])
    {
        param->axisL.x += 1;
    }

    if (keys[SDL_SCANCODE_8])
    {
        param->axisR.y += -1;
    }
    if (keys[SDL_SCANCODE_2])
    {
        param->axisR.y += 1;
    }
    if (keys[SDL_SCANCODE_4])
    {
        param->axisR.x += -1;
    }
    if (keys[SDL_SCANCODE_6])
    {
        param->axisR.x += 1;
    }
}

void Keybord::scanButton(ControllerParam *param)
{
    if (keys[SDL_SCANCODE_P])
    {
        param->buttonDown[CT_DECITION_OR_ATTACK] = true;
        param->buttonUp[CT_DECITION_OR_ATTACK] = false;
    }
    else
    {
        param->buttonDown[CT_DECITION_OR_ATTACK] = false;
        param->buttonUp[CT_DECITION_OR_ATTACK] = true;
    }

    if (keys[SDL_SCANCODE_I])
    {
        param->buttonDown[CT_GUARD] = true;
        param->buttonUp[CT_GUARD] = false;
    }
    else
    {
        param->buttonDown[CT_GUARD] = false;
        param->buttonUp[CT_GUARD] = true;
    }

    if (keys[SDL_SCANCODE_U])
    {
        param->buttonDown[CT_GRUB] = true;
        param->buttonUp[CT_GRUB] = false;
    }
    else
    {
        param->buttonDown[CT_GRUB] = false;
        param->buttonUp[CT_GRUB] = true;
    }

    if (keys[SDL_SCANCODE_5])
    {
        param->buttonDown[CT_PRDGDIRECTION] = true;
        param->buttonUp[CT_PRDGDIRECTION] = false;
    }
    else
    {
        param->buttonDown[CT_PRDGDIRECTION] = false;
        param->buttonUp[CT_PRDGDIRECTION] = true;
    }

    if (keys[SDL_SCANCODE_SPACE])
    {
        param->buttonDown[CT_PAUSE] = true;
        param->buttonUp[CT_PAUSE] = false;
    }
    else
    {
        param->buttonDown[CT_PAUSE] = false;
        param->buttonUp[CT_PAUSE] = true;
    }

    if (keys[SDL_SCANCODE_BACKSPACE])
    {
        param->buttonDown[CT_CANCEL] = true;
        param->buttonUp[CT_CANCEL] = false;
    }
    else
    {
        param->buttonDown[CT_CANCEL] = false;
        param->buttonUp[CT_CANCEL] = true;
    }

    if (keys[SDL_SCANCODE_Q] || keys[SDL_SCANCODE_E])
    {
        param->buttonDown[CT_JUMP] = true;
        param->buttonUp[CT_JUMP] = false;
    }
    else
    {
        param->buttonDown[CT_JUMP] = false;
        param->buttonUp[CT_JUMP] = true;
    }

    for(int i = 0; i < 12; i++){
        if(param->buttonDown[i] == true){
            count[i]++;
        }
        else{ 
            count[i] = 0;
        }
    }

    for (int i = 0; i < 12; i++)
    {
        if (count[i] > 1)
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
    bool ret = BaseController::updateEvent();
    keys = SDL_GetKeyboardState(NULL);
    return ret;
}

bool Keybord::scanEndFlag()
{
    if (BaseController::scanEndFlag())
    {
        return true;
    }
    if (keys[SDL_SCANCODE_ESCAPE])
    {
        return true;
    }
    return false;
}
