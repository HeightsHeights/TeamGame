
#pragma once

#include "./netConnector.h"

/******************************************************************************
 * class NetworkManager
 * 機能1：
******************************************************************************/
class NetworkManager
{
private:
  static int gSocket;
  static fd_set gMask;
  static int gWidth;
  static NetConnector *connector;
  static void setMask(void);

public:
  static int getGSocket() { return gSocket; }

  static bool init(const char *hostName);
  static bool connect();
  static void disconnect();
  static bool waitRequest(fd_set *readOK);

  static void sendData(void *data, int dataSize);
  static int recvData(void *data, int dataSize);
};
