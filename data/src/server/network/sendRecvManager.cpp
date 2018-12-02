/******************************************************************************
 * ネットワーク関係に必要なヘッダーの読み込み
******************************************************************************/
#include "./sendRecvManager.h"
#include <unistd.h>
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