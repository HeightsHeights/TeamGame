#ifdef _ENABLE_WII

#pragma once

/******************************************************************************
 * コントローラー関係に必要なヘッダーの読み込み
******************************************************************************/
#include "../../common/controllerParam/controllerParam.h"
#include "./baseController.h"
extern "C"
{
#include <libcwiimote/wiimote.h>
#include <libcwiimote/wiimote_api.h>
}
/******************************************************************************
 * class WiiRemoteController
******************************************************************************/
class WiiRemote : public BaseController
{
private:
  wiimote_t wiimote = WIIMOTE_INIT;
  virtual void scanDirection(ControllerParam *param);
  virtual void scanButton(ControllerParam *param);

public:
  WiiRemote() {}
  WiiRemote(wiimote_t wiimote) { this->wiimote = wiimote; }
  virtual void cleanUp() { wiimote_disconnect(&this->wiimote); }
  virtual bool updateEvent();
  virtual bool scanEndFlag();
};

#endif