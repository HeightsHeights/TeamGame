#include "./baseController.h"

void BaseController::scanDirection(ControllerParam *param)
{
}
void BaseController::scanButton(ControllerParam *param)
{
}

ControllerParam BaseController::readStateController()
{
    ControllerParam param = ControllerParam();

    //方向入力値をVector2f型で代入する
    scanDirection(&param);

    //ボタンの状態を入力する
    scanButton(&param);

    return param;
}

void BaseController::updateEvent()
{
    SDL_PollEvent(&event);
}