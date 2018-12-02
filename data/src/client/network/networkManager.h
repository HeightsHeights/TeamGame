
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
  static NetConnector *connector;

public:
  static bool init(char *hostName);
  static bool connect();
  static void disconnect();

  void sendData(void *data, int dataSize);
  int recieveData(void *data, int dataSize);
};
