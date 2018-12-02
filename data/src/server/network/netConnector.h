
#pragma once

#include <netdb.h>
/******************************************************************************
 * class NetConnector
******************************************************************************/
class NetConnector
{
private:
  int gSocket;
  sockaddr_in server;

public:
  NetConnector();
  NetConnector(int gSocket, sockaddr_in server);
  bool connectClient();
  void disconnectClient();
};