#pragma once

#define MAX_CLIENTS 4
#define ALL_CLIENTS -1
typedef struct
{
  int fd;
  char name[256];
} Client;

/******************************************************************************
 * class SendRecvManager
 * 機能1：
******************************************************************************/
class SendRecvManager
{
private:
  int gSocket;
  int gClientNum;
  Client gClients[MAX_CLIENTS];

public:
  SendRecvManager();
  SendRecvManager(int gSocket, int gClientNum, Client clients[]);
  void sendData(int pos, void *data, int dataSize);
  int recieveData(int pos, void *data, int dataSize);
};