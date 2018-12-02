
#pragma once

#include "./netConnector.h"
#include "./sendRecvManager.h"

/******************************************************************************
 * class NetworkManager
 * 機能1：
******************************************************************************/
class NetworkManager
{
private:
  static int srcSocket;
  static fd_set gMask;
  static int gWidth;
  static SendRecvManager *sendRecvManager;
  static NetConnector *connector;
  static void setMack(int maxFd);

public:
  static SendRecvManager *getSendRecvManager();
  static bool init();
  static bool connect();
  static bool disconnect();
  static void closeAll();
};
