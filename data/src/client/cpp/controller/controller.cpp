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
}

void Joystick::scanAnalogStick(ControllerParam *param)
{
    //アナログスティックからの値を-1~1にする←
}
void Joystick::scanButton(ControllerParam *param)
{
    //ButtonUp/Down/State←
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
Joystick ControllerManager::joystick = NULL;

bool ControllerManager::init()
{
    //接続があるか確認←

    //成功すればコントローラーの初期化にこれを使ってください 0のところにコントローラーのIDが来ます←
    joystick = *new Joystick(0);
}
int ControllerManager::updateController()
{
    //SDLの更新

    //コントローラーの更新

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
}