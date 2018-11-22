/******************************************************************************
 * ネットワーク関係に必要なヘッダーの読み込み
******************************************************************************/
#include "./network.h"
#include <stdio.h>
#include <unistd.h>
#include <strings.h>
#include <assert.h>
/******************************************************************************
 * class SendRecvManager
******************************************************************************/
SendRecvManager::SendRecvManager()
{
}
SendRecvManager::SendRecvManager(int gSocket)
{
    this->gSocket = gSocket;
}
void SendRecvManager::sendData(void *data, int dataSize)
{
    /* 引き数チェック */
    assert(data != NULL);
    assert(0 < dataSize);

    write(gSocket, data, dataSize);
}
int SendRecvManager::recieveData(void *data, int dataSize)
{
    /* 引き数チェック */
    assert(data != NULL);
    assert(0 < dataSize);

    return read(gSocket, data, dataSize);
}
/******************************************************************************
 * class NetConnector
******************************************************************************/
NetConnector::NetConnector()
{
}
NetConnector::NetConnector(int gSocket, sockaddr_in server)
{
    this->gSocket = gSocket;
    this->server = server;
}
bool NetConnector::connectServer()
{
    if (connect(gSocket, (struct sockaddr *)&server, sizeof(server)) == -1)
    {
        fprintf(stderr, "ERROR --> cannot connect\n");
        close(gSocket);
        return false;
    }
    fprintf(stderr, "connected\n");
    return true;
}
void NetConnector::disconnectServer()
{
    printf("...Connection closed\n");
    close(gSocket);
}
/******************************************************************************
 * class NetworkManager
******************************************************************************/
SendRecvManager NetworkManager::sendRecvManager;
NetConnector NetworkManager::connector;

bool NetworkManager::init(char *hostName)
{
    struct hostent *servHost;
    struct sockaddr_in server;

    /* ホスト名からホスト情報を得る */
    if ((servHost = gethostbyname(hostName)) == NULL)
    {
        fprintf(stderr, "ERROR --> Unknown host\n");
        return false;
    }

    bzero((char *)&server, sizeof(server));
    server.sin_family = AF_INET;
    server.sin_port = htons(PORT);
    bcopy(servHost->h_addr, (char *)&server.sin_addr, servHost->h_length);

    /* ソケットを作成する */
    int gSocket;
    if ((gSocket = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        fprintf(stderr, "socket allocation failed\n");
        return false;
    }
    connector = *new NetConnector(gSocket, server);

    return true;
}
SendRecvManager NetworkManager::getSendRecvManager()
{
    return sendRecvManager;
}
bool NetworkManager::connect()
{
    if (!connector.connectServer())
    {
        fprintf(stderr, "ERROR --> connectServer()\n");
        return false;
    }
    return true;
}
void NetworkManager::disconnect()
{
    connector.disconnectServer();
}