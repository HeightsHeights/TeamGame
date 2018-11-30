#ifdef _ENABLE_WII

#pragma once

/******************************************************************************
 * コントローラー関係に必要なヘッダーの読み込み
******************************************************************************/
#include "../../common/controllerParam/controllerParam.h"
#include "./baseController.h"
extern "C" {
#include <libcwiimote/wiimote.h>     // Wiiリモコンを用いるために必要なヘッダファイル
#include <libcwiimote/wiimote_api.h> // Wiiリモコンを用いるために必要なヘッダファイル
}
/******************************************************************************
 * class WiiRemoteController
******************************************************************************/
class WiiRemoteController : public BaseController
{
private:
  wiimote_t wiimote = WIIMOTE_INIT;
  virtual void scanDirection(ControllerParam *param);
  virtual void scanButton(ControllerParam *param);

public:
  WiiRemoteController() {}
  virtual bool updateEvent();
  WiiRemoteController *connect(const char *id);
};

#endif