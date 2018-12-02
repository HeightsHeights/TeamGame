#include "./mainProgram.h"
#include "../network/network.h"

/******************************************************************************
 * メイン関数
******************************************************************************/
int main(int argc, char *argv[])
{
    GameSystem *gameSystem = new GameSystem();

    if (!gameSystem->init(argc, argv))
    {
        return -1;
    }
    if (gameSystem->gameLoop())
    {
        return -1;
    }
    if (!gameSystem->terminate())
    {
        return -1;
    }
    return 0;
}
