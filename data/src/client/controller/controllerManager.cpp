/******************************************************************************
 * コントローラー関係に必要なヘッダーの読み込み
******************************************************************************/

#include "./controllerManager.h"
#include "./joystick.h"
#include "./keybord.h"

/******************************************************************************
 * class ControllerManager
******************************************************************************/
BaseController ControllerManagercontroller;

bool ControllerManager::init()
{
    //接続があるか確認←
    if (SDL_NumJoysticks() > 0)
    {
        controller = Joystick(0);
    }
    else
    {
        fprintf(stderr, "Error --> connot connect joystick\n");
        controller = Keybord();
    }
    return true;
}
int ControllerManager::updateController()
{
    //SDLの更新←
    controller.updateEvent();

    ControllerParam param = controller.readStateController();

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