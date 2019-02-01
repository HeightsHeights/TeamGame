#include "controllerParam.h"

ControllerParam::ControllerParam()
{
    for (int i = 0; i < MAX_BUTTON; i++)
    {
        this->buttonDown[i] = false;
        this->buttonUp[i] = false;
        this->buttonState[i] = false;
    }
}