#include "./networkManager.h"
#include <stdio.h>
#include <strings.h>
#include <unistd.h>
#include <assert.h>

#define PORT (u_short)8888 /* ポート番号 */
/******************************************************************************
 * class NetworkManager
******************************************************************************/
int NetworkManager::srcSocket;
fd_set NetworkManager::gMask;
int NetworkManager::gWidth;
int NetworkManager::gClientNum;
Client NetworkManager::gClients[MAX_PLAYERS];
NetConnector *NetworkManager::connector;

void NetworkManager::setMask(int maxFd)
{
    gWidth = maxFd + 1;

    FD_ZERO(&gMask);
    for (int i = 0; i < gClientNum; i++)
    {
        FD_SET(gClients[i].fd, &gMask);
    }
}

bool NetworkManager::init()
{
    gClientNum = MAX_CLIENTS;
    struct sockaddr_in server;
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

    connector = new NetConnector(srcSocket, server);
    int maxFd = connect();
    if (maxFd == -1)
    {
        return false;
    }
    setMask(maxFd);

    close(srcSocket);
    fprintf(stderr, "Accept client\n");
    return true;
}

int NetworkManager::connect()
{
    int dstSocket;
    for (int i = 0; i < MAX_PLAYERS; i++)
    {
        if ((dstSocket = accept(srcSocket, NULL, NULL)) == -1)
        {
            fprintf(stderr, "Accept error\n");
            for (int j = 0; j < i; j++)
            {
                disconnect(j);
            }
            return -1;
        }
        gClients[i].fd = dstSocket;
    }
    return dstSocket;
}
void NetworkManager::disconnect(int id)
{
    close(gClients[id].fd);
}
void NetworkManager::closeAll()
{
    for (int i = 0; i < gClientNum; i++)
    {
        disconnect(i);
    }
}

bool NetworkManager::waitRequest(fd_set *readOK)
{
    *readOK = gMask;
    /* クライアントからデータが届いているか調べる */
    if (select(gWidth, readOK, NULL, NULL, NULL) < 0)
    {
        /* エラーが起こった */
        return false;
    }
    return true;
}

void NetworkManager::sendData(int pos, void *data, int dataSize)
{
    /* 引き数チェック */
    assert(0 <= pos && pos < gClientNum || pos == ALL_CLIENTS);
    assert(data != NULL);
    assert(0 < dataSize);

    if (pos == ALL_CLIENTS)
    {
        /* 全クライアントにデータを送る */
        for (int i = 0; i < gClientNum; i++)
        {
            write(gClients[i].fd, data, dataSize);
        }
    }
    else
    {
        write(gClients[pos].fd, data, dataSize);
    }
}
int NetworkManager::recvData(int pos, void *data, int dataSize)
{
    int n;

    assert(0 <= pos && pos < gClientNum);
    assert(data != NULL);
    assert(0 < dataSize);

    n = read(gClients[pos].fd, data, dataSize);

    return n;
}