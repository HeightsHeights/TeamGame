/******************************************************************************
 * コントローラー関係に必要なヘッダーの読み込み
******************************************************************************/

#include "./controllerManager.h"

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