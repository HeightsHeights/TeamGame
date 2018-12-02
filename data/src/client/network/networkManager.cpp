#include "./networkManager.h"
#include <stdio.h>
#include <strings.h>

#define PORT (u_short)8888 /* ポート番号 */
/******************************************************************************
 * class NetworkManager
******************************************************************************/
SendRecvManager *NetworkManager::sendRecvManager;
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
    int gSocket;
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
    sendRecvManager = new SendRecvManager(gSocket);
    if (sendRecvManager == NULL)
    {
        fprintf(stderr, "sendRecvManaer making failed\n");
        return false;
    }

    return true;
}
SendRecvManager *NetworkManager::getSendRecvManager()
{
    return sendRecvManager;
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