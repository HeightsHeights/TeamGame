/******************************************************************************
 * コントローラー関係に必要なヘッダーの読み込み
******************************************************************************/

#include "./controllerManager.h"
#include "./joystick.h"
#include "./keybord.h"
#include "./wiiRemoteConnector.h"
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
        fprintf(stderr, "Connect Joystick!\n");
        controller = new Joystick(0);
    }
    else
    {
        fprintf(stderr, "Connect Keybord!\n");
        controller = new Keybord();
    }
    return true;
}
bool ControllerManager::updateController()
{
    controller->updateEvent();

    ControllerParam param = controller->readStateController();

    bool endFlag = requestReaction(param);

    return controller->scanEndFlag() || endFlag;
}
bool ControllerManager::requestReaction(ControllerParam param)
{
    //シーンマネージャーにparamを渡します
    return SceneManager::reactController(param);
}
void ControllerManager::cleanUp()
{
    //コントローラーの終了処理←
    controller->cleanUp();
    delete controller;
}
#ifdef _ENABLE_WII
bool ControllerManager::connectWiiRemote(const char *id)
{
    fprintf(stderr, "Connect WiiRemote......\n");
    WiiRemote *wiiRemote = WiiRemoteConnector().connect(id);

    if (wiiRemote == NULL)
    {
        fprintf(stderr, "Error --> Cannot connect WiiRemote\n");
        return false;
    }
    fprintf(stderr, "Connected!\n");
    controller = wiiRemote;
    return true;
}
#endif