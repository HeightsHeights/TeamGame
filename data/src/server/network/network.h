#pragma once

#define PORT (u_short)8888 /* ポート番号 */
#define MAX_CLIENTS 4
#define ALL_CLIENTS -1
typedef struct
{
  int fd;
  char name[256];
} Client;
/******************************************************************************
 * ネットワーク関係に必要なヘッダーの読み込み
******************************************************************************/
#include <sys/socket.h>
#include <netdb.h>
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
/******************************************************************************
 * class NetConnector
 * 機能1：
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
  static SendRecvManager sendRecvManager;
  static NetConnector connector;
  static void setMack(int maxFd);

public:
  static SendRecvManager getSendRecvManager();
  static bool init();
  static bool connect();
  static bool disconnect();
  static void closeAll();
};
