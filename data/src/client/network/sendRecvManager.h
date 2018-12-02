#pragma once

/******************************************************************************
 * class SendRecvManager
 * 機能1：
******************************************************************************/
class SendRecvManager
{
private:
  int gSocket;

public:
  SendRecvManager();
  SendRecvManager(int gSocket);
  void sendData(void *data, int dataSize);
  int recieveData(void *data, int dataSize);
};
