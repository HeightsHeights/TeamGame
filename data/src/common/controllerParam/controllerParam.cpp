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

ControllerParam ControllerParam::operator=(ControllerParam other)
{
    this->axisR = other.axisR;
    this->axisL = other.axisL;

    for (int i = 0; i < MAX_BUTTON; i++)
    {
        this->buttonDown[i] = other.buttonDown[i];
        this->buttonUp[i] = other.buttonUp[i];
        this->buttonState[i] = other.buttonState[i];
    }
    return *this;
}
