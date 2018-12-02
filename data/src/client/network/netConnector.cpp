#include "./netConnector.h"
#include <stdio.h>
#include <unistd.h>
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
