/******************************************************************************
 * ネットワーク関係に必要なヘッダーの読み込み
******************************************************************************/
#include "../../header/network/network.h"
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
SendRecvManager::SendRecvManager(int gSocket, int gClientNum, Client clients[])
{
    this->gSocket = gSocket;
    this->gClientNum = gClientNum;
    for (int i = 0; i < MAX_CLIENTS; i++)
    {
        this->gClients[i] = clients[i];
    }
}
void SendRecvManager::sendData(int pos, void *data, int dataSize)
{
    int i;

    /* 引き数チェック */
    assert(0 <= pos && pos < gClientNum || pos == ALL_CLIENTS);
    assert(data != NULL);
    assert(0 < dataSize);

    if (pos == ALL_CLIENTS)
    {
        /* 全クライアントにデータを送る */
        for (i = 0; i < gClientNum; i++)
        {
            write(gClients[i].fd, data, dataSize);
        }
    }
    else
    {
        write(gClients[pos].fd, data, dataSize);
    }
}
int SendRecvManager::recieveData(int pos, void *data, int dataSize)
{
    int n;

    assert(0 <= pos && pos < gClientNum);
    assert(data != NULL);
    assert(0 < dataSize);

    n = read(gClients[pos].fd, data, dataSize);

    return n;
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
bool NetConnector::connectClient()
{
}
void NetConnector::disconnectClient()
{
}
/******************************************************************************
 * class NetworkManager
******************************************************************************/
SendRecvManager NetworkManager::sendRecvManager;
NetConnector NetworkManager::connector;

bool NetworkManager::init()
{
    struct sockaddr_in server;
    int srcSocket;
    int dstSocket;
    int val = 1;

    bzero((char *)&server, sizeof(server));
    server.sin_family = AF_INET;
    server.sin_port = htons(PORT);
    server.sin_addr.s_addr = htonl(INADDR_ANY);

    /* ソケットを作成する */
    if ((srcSocket = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        fprintf(stderr, "Socket allocation failed\n");
        return false;
    }
    setsockopt(srcSocket, SOL_SOCKET, SO_REUSEADDR, &val, sizeof(val));

    /* ソケットに名前をつける */
    if (bind(srcSocket, (struct sockaddr *)&server, sizeof(server)) == -1)
    {
        fprintf(stderr, "Cannot bind\n");
        close(srcSocket);
        return false;
    }
    fprintf(stderr, "Successfully bind!\n");

    /* クライアントからの接続要求を待つ */
    if (listen(srcSocket, 1) == -1)
    {
        fprintf(stderr, "Cannot listen\n");
        close(srcSocket);
        return false;
    }
    fprintf(stderr, "Listen OK\n");

    if ((dstSocket = accept(srcSocket, NULL, NULL)) == -1)
    {
        fprintf(stderr, "Accept error\n");
        close(srcSocket);
        return false;
    }
    close(srcSocket);
    fprintf(stderr, "Accept client\n");
    close(dstSocket);
    return true;
}

SendRecvManager NetworkManager::getSendRecvManager()
{
    return sendRecvManager;
}

bool NetworkManager::connect()
{
}