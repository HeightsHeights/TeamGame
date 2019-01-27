
#pragma once

#include <netdb.h>
/******************************************************************************
 * class NetConnector
 * 機能1：
******************************************************************************/
class NetConnector
{
private:
  int gSocket;
  sockaddr_in server;

  bool isConnected;

public:
  NetConnector();
  NetConnector(int gSocket, sockaddr_in server);
  bool connectServer();
  void disconnectServer();
};
