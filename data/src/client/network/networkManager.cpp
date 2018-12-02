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
NetConnector *NetworkManager::connector;

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
    if ((gSocket = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        fprintf(stderr, "socket allocation failed\n");
        return false;
    }

    connector = new NetConnector(gSocket, server);
    if (connector == NULL)
    {
        fprintf(stderr, "connector making failed\n");
        return false;
    }

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

void NetworkManager::sendData(void *data, int dataSize)
{
    /* 引き数チェック */
    assert(data != NULL);
    assert(0 < dataSize);

    write(gSocket, data, dataSize);
}
int NetworkManager::recieveData(void *data, int dataSize)
{
    /* 引き数チェック */
    assert(data != NULL);
    assert(0 < dataSize);

    return read(gSocket, data, dataSize);
}
