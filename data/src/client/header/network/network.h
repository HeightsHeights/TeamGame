#pragma once

#define PORT (u_short)8888 /* ポート番号 */
/******************************************************************************
 * ネットワーク関係に必要なヘッダーの読み込み
******************************************************************************/
#include <stdio.h>
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
 * class NetSender
 * 機能1：
******************************************************************************/
class NetSender
{
private:
  int gSocket;

public:
  NetSender(int gSocket);
  void sendData(void *data, int dataSize);
};
/******************************************************************************
 * class NetReciever
 * 機能1：
******************************************************************************/
class NetReciever
{
private:
  int gSocket;

public:
  NetReciever(int gSocket);
  void recieveData(void *data, int dataSize);
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
  static NetSender sender;
  static NetReciever reciever;
  static NetConnector connector;

public:
  static NetSender getSender();
  static NetReciever getReciever();
  static bool init(char *hostName);
  static bool connect();
  static bool disconnect();
  static void send(void *data, int dataSize);
  static void recieve(void *data, int dataSize);
};
