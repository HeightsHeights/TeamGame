#pragma once

/******************************************************************************
 * ネットワーク関係に必要なヘッダーの読み込み
******************************************************************************/

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
public:
  void sendData(void *data, int dataSize);
};
/******************************************************************************
 * class NetReciever
 * 機能1：
******************************************************************************/
class NetReciever
{
private:
public:
  void recieveData(void *data, int dataSize);
};
/******************************************************************************
 * class NetConnector
 * 機能1：
******************************************************************************/
class NetConnector
{
private:
  NetSender sender;
  NetReciever reciever;

public:
  NetConnector(NetSender sender, NetReciever reciever);
  bool connectServer(); //引数にサーバー情報
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

public:
  static bool init();
  static bool connect();
  static void send(void *data, int dataSize);
  static void recieve(void *data, int dataSize);
};
