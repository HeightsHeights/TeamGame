/******************************************************************************
 * コントローラー関係に必要なヘッダーの読み込み
******************************************************************************/

#include "./controllerManager.h"
#include "./joystick.h"
#include "./keybord.h"
#include "./wiiRemoteController.h"
#include "../scene/sceneManager.h"

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
    return true;
}
bool ControllerManager::updateController()
{
    controller->updateEvent();

    ControllerParam param = controller->readStateController();

    requestReaction(param);

    return controller->scanEndFlag();
}
void ControllerManager::requestReaction(ControllerParam param)
{
    //シーンマネージャーにparamを渡します
    SceneManager::reactController(param);
}
void ControllerManager::cleanUp()
{
    //コントローラーの終了処理←
    //SDL_JoystickClose(joystick);
}
#ifdef _ENABLE_WII
bool ControllerManager::connectWiiRemoteController(const char *id)
{
    fprintf(stderr, "Connect WiiRemote......\n");
    WiiRemoteController *wiiController = new WiiRemoteController();
    wiiController = wiiController->connect(id);
    if (wiiController == NULL)
    {
        fprintf(stderr, "Error --> connot connect wii\n");
        delete wiiController;
        return false;
    }
    fprintf(stderr, "Connected!\n");
    controller = wiiController;
    return true;
}
#endif