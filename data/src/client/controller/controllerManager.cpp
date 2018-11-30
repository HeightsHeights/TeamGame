/******************************************************************************
 * コントローラー関係に必要なヘッダーの読み込み
******************************************************************************/

#include "./controllerManager.h"
#include "./joystick.h"
#include "./keybord.h"
#include "./wiiRemoteController.h"

/******************************************************************************
 * class ControllerManager
******************************************************************************/
BaseController *ControllerManager::controller;

bool ControllerManager::init()
{
    //接続があるか確認←
    if (SDL_NumJoysticks() > 0)
    {
        controller = new Joystick(0);
    }
    else
    {
        fprintf(stderr, "Error --> connot connect joystick\n");
        controller = new Keybord();
    }
#ifdef _ENABLE_WII
    controller = WiiRemoteController().connect("88");
    if (controller == NULL)
    {
        fprintf(stderr, "Error --> connot connect wii\n");
        controller = new Keybord();
    }
#endif
    return true;
}
int ControllerManager::updateController()
{
    controller->updateEvent();

    ControllerParam param = controller->readStateController();

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