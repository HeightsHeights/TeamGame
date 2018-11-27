#ifdef USE_WII

#pragma once

/******************************************************************************
 * コントローラー関係に必要なヘッダーの読み込み
******************************************************************************/
#include "../../common/controllerParam/controllerParam.h"
#include "./baseController.h"
#include <libcwiimote/wiimote.h>     // Wiiリモコンを用いるために必要なヘッダファイル
#include <libcwiimote/wiimote_api.h> // Wiiリモコンを用いるために必要なヘッダファイル
/******************************************************************************
 * class WiiRemoteController
******************************************************************************/
class WiiRemoteController : public BaseController
{
private:
  wiimote_t wiimote;
  virtual void scanDirection(ControllerParam *param);
  virtual void scanButton(ControllerParam *param);

public:
  WiiRemoteController() { this->wiimote = WIIMOTE_INIT; }
  virtual bool updateEvent();
};

#endif