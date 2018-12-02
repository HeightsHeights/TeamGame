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
bool NetConnector::connectClient()
{
}
void NetConnector::disconnectClient()
{
}