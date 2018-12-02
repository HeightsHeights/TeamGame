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
SendRecvManager::SendRecvManager(int gSocket)
{
    this->gSocket = gSocket;
}
void SendRecvManager::sendData(void *data, int dataSize)
{
    /* 引き数チェック */
    assert(data != NULL);
    assert(0 < dataSize);

    write(gSocket, data, dataSize);
}
int SendRecvManager::recieveData(void *data, int dataSize)
{
    /* 引き数チェック */
    assert(data != NULL);
    assert(0 < dataSize);

    return read(gSocket, data, dataSize);
}
