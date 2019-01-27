#include "./netConnector.h"
#include <stdio.h>
#include <unistd.h>
/******************************************************************************
 * class NetConnector
******************************************************************************/
bool NetConnector::isConnected = false;

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
    isConnected = true;
    return true;
}
void NetConnector::disconnectServer()
{
    if (isConnected)
    {
        printf("...Connection closed\n");
        close(gSocket);
    }
}
