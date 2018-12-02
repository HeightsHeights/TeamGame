
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
    static SendRecvManager *sendRecvManager;
    static NetConnector *connector;

  public:
    static SendRecvManager *getSendRecvManager();
    static bool init(char *hostName);
    static bool connect();
    static void disconnect();
};
