/******************************************************************************
 * コントローラー関係に必要なヘッダーの読み込み
******************************************************************************/
#include "./controller.h"

/******************************************************************************
 * class Joystick
******************************************************************************/
Joystick::Joystick()
{
    //書かない
}

Joystick::Joystick(const unsigned int controllerID)
{
    //コントローラーの初期化 IDは引数←
    joy = SDL_JoystickOpen(controllerID);
}

void Joystick::scanAnalogStick(ControllerParam *param)
{
    //アナログスティックからの値を-1~1にする←
    param->axisL.x = SDL_JoystickGetAxis(joy, 0) / MAX_ANALOG_STICK_AXIS;

    if (param->axisL.x > 1)
    {
        param->axisL.x = 1;
    }
    else if (param->axisL.x < -1)
    {
        param->axisL.x = -1;
    }

    param->axisL.y = SDL_JoystickGetAxis(joy, 1) / MAX_ANALOG_STICK_AXIS;

    if (param->axisL.y > 1)
    {
        param->axisL.y = 1;
    }
    else if (param->axisL.y < -1)
    {
        param->axisL.y = -1;
    }

    param->axisR.x = SDL_JoystickGetAxis(joy, 2) / MAX_ANALOG_STICK_AXIS;

    if (param->axisR.x > 1)
    {
        param->axisR.x = 1;
    }
    else if (param->axisR.x < -1)
    {
        param->axisR.x = -1;
    }

    param->axisR.y = SDL_JoystickGetAxis(joy, 3) / MAX_ANALOG_STICK_AXIS;

    if (param->axisR.y > 1)
    {
        param->axisR.y = 1;
    }
    else if (param->axisR.y < -1)
    {
        param->axisR.y = -1;
    }
}
void Joystick::scanButton(ControllerParam *param)
{
    //ButtonUp/Down/State←
    for (int i = 0; i > 12; i++)
    {
        if (SDL_JoystickGetButton(joy, i) > 0)
        {
            param->buttonDown[i] = true;
            param->buttonUp[i] = false;
        }
        else
        {
            param->buttonUp[i] = true;
            param->buttonDown[i] = false;
        }

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

ControllerParam Joystick::readStateController()
{
    ControllerParam param = ControllerParam();

    //アナログスティックの値をVector2fに代入する
    scanAnalogStick(&param);

    //ボタンの状態を入力する
    scanButton(&param);

    return param;
}

/******************************************************************************
 * class ControllerManager
******************************************************************************/
Joystick ControllerManager::joystick;

bool ControllerManager::init()
{
    //接続があるか確認←
    if (SDL_NumJoysticks() > 0)
    {
        joystick = Joystick(0);
    }
    else
    {
        fprintf(stderr, "Error --> connot connect joystick\n");
        return false;
    }
    return true;
}
int ControllerManager::updateController()
{
    //SDLの更新←

    //コントローラーの更新←
    SDL_JoystickUpdate();
    ControllerParam param = joystick.readStateController();

    requestReaction(param);
}
void ControllerManager::requestReaction(ControllerParam param)
{
    //シーンマネージャーにparamを渡します
    //今は書く必要はありません
}
void ControllerManager::cleanUp()
{
    //コントローラーの終了処理←
    //SDL_JoystickClose(joystick);
}