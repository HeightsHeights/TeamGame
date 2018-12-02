
#pragma once

#include "./netConnector.h"

#define MAX_CLIENTS 4
#define ALL_CLIENTS -1

typedef struct
{
  int fd;
  char name[256];
} Client;

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
  static int gClientNum;
  static Client gClients[MAX_CLIENTS];
  static NetConnector *connector;
  static void setMask(int maxFd);

public:
  static bool init();
  static bool connect(int srcSocket);
  static void disconnect(int id);
  static void closeAll();
  static bool waitRequest(fd_set *readOK);
  static bool recvEvent();

  static void sendData(int pos, void *data, int dataSize);
  static int recvData(int pos, void *data, int dataSize);
};
