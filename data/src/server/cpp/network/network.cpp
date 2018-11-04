/******************************************************************************
 * ネットワーク関係に必要なヘッダーの読み込み
******************************************************************************/
#include "../../header/network/network.h"
#include <stdio.h>
#include <unistd.h>
#include <strings.h>
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
}
void NetConnector::disconnectServer()
{
}
/******************************************************************************
 * class NetworkManager
******************************************************************************/
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

bool NetworkManager::connect()
{
}