#include "./baseController.h"

void BaseController::scanDirection(ControllerParam *param)
{
}
void BaseController::scanButton(ControllerParam *param)
{
}

void BaseController::cleanUp()
{
}
ControllerParam BaseController::readStateController()
{
    ControllerParam param = ControllerParam();

    //方向入力値をVector2f型で代入する
    scanDirection(&param);

    //ボタンの状態を入力する
    scanButton(&param);

    if (scanEndFlag())
    {
        param.buttonDown[CT_FINISH] = true;
        param.buttonState[CT_FINISH] = true;
    }

    return param;
}

bool BaseController::scanEndFlag()
{
    if (event.type != SDL_QUIT)
    {
        return false;
    }
    return true;
}

bool BaseController::updateEvent()
{
    return SDL_PollEvent(&event);
}