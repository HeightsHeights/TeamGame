#pragma once

#define PORT (u_short)8888 /* ポート番号 */
/******************************************************************************
 * ネットワーク関係に必要なヘッダーの読み込み
******************************************************************************/
#include <sys/socket.h>
#include <netdb.h>
/******************************************************************************
 * class DataBlockGenerator
 * 機能1：
******************************************************************************/
class DataBlockGenerator
{
private:
public:
  void setDataBlock(void *dataBlock, void *data, int *dataSize);
};
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
  bool connectServer();
  void disconnectServer();
};

/******************************************************************************
 * class NetworkManager
 * 機能1：
******************************************************************************/
class NetworkManager
{
private:
  static DataBlockGenerator dataBlockGenerator;
  static SendRecvManager sendRecvManager;
  static NetConnector connector;

public:
  static SendRecvManager getSendRecvManager();
  static bool init(char *hostName);
  static bool connect();
  static void disconnect();
};
