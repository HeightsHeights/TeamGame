#include <stdlib.h>
#include <SDL2/SDL.h>
#include "./mainProgram.h"
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
    if (!gameSystem->gameLoop())
    {
        return -1;
    }
    if (!gameSystem->terminate())
    {
        return -1;
    }
    return 0;
}