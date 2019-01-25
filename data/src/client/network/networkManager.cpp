#include "./networkManager.h"
#include <stdio.h>
#include <strings.h>
#include <unistd.h>
#include <assert.h>

#define PORT (u_short)8888 /* ポート番号 */
/******************************************************************************
 * class NetworkManager
******************************************************************************/
int NetworkManager::gSocket;
fd_set NetworkManager::gMask;
int NetworkManager::gWidth;
NetConnector *NetworkManager::connector;

void NetworkManager::setMask()
{
    FD_ZERO(&gMask);
    FD_SET(gSocket, &gMask);

    gWidth = gSocket + 1;
}

bool NetworkManager::init(const char *hostName)
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
    if ((gSocket = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        fprintf(stderr, "socket allocation failed\n");
        return false;
    }

    if (connector != NULL)
    {
        delete connector;
    }
    connector = new NetConnector(gSocket, server);
    if (connector == NULL)
    {
        fprintf(stderr, "connector making failed\n");
        return false;
    }
    setMask();
    return true;
}

bool NetworkManager::connect()
{
    if (!connector->connectServer())
    {
        fprintf(stderr, "ERROR --> connectServer()\n");
        return false;
    }
    return true;
}
void NetworkManager::disconnect()
{
    connector->disconnectServer();
}
bool NetworkManager::waitRequest(fd_set *readOK)
{
    struct timeval timeout;

    timeout.tv_sec = 0;
    timeout.tv_usec = 20;

    *readOK = gMask;
    if (select(gWidth, readOK, NULL, NULL, &timeout) < 0)
    {
        return false;
    }
    return true;
}
void NetworkManager::sendData(void *data, int dataSize)
{
    /* 引き数チェック */
    assert(data != NULL);
    assert(0 < dataSize);

    write(gSocket, data, dataSize);
}
int NetworkManager::recvData(void *data, int dataSize)
{
    /* 引き数チェック */
    assert(data != NULL);
    assert(0 < dataSize);

    return read(gSocket, data, dataSize);
}
