/******************************************************************************
 * コントローラー関係に必要なヘッダーの読み込み
******************************************************************************/
#include "../../header/controller/controller.h"

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
    param->axisL.x = SDL_JoystickGetAxis(joy, 0) / (float)32767;

    if (param->axisL.x > 1)
    {
        param->axisL.x = 1;
    }
    else if (param->axisL.x < -1)
    {
        param->axisL.x = -1;
    }

    param->axisL.y = SDL_JoystickGetAxis(joy, 1) / (float)32767;

    if (param->axisL.y > 1)
    {
        param->axisL.y = 1;
    }
    else if (param->axisL.y < -1)
    {
        param->axisL.y = -1;
    }

    param->axisR.x = SDL_JoystickGetAxis(joy, 2) / (float)32767;

    if (param->axisR.x > 1)
    {
        param->axisR.x = 1;
    }
    else if (param->axisR.x < -1)
    {
        param->axisR.x = -1;
    }

    param->axisR.y = SDL_JoystickGetAxis(joy, 3) / (float)32767;

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
    ControllerParam param = *new ControllerParam();

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
        //成功すればコントローラーの初期化にこれを使ってください 0のところにコントローラーのIDが来ます←
        joystick = *new Joystick(0);
    }
    else
    {
        printf("error connect joystick\n");
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