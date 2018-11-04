#include <stdlib.h>
#include <SDL/SDL.h>
#include "../../header/main/mainProgram.h"
#include "../../header/network/network.h"
/******************************************************************************
 * メイン関数
******************************************************************************/
int main(int argc, char *argv[])
{
    int num;
    /* コマンド引数確認 */
    if (argc == 1)
    {
        num = MAX_CLIENTS;
    }
    else if (argc != 2)
    {
        fprintf(stderr, "Usage: number of clients\n");
        return -1;
    }
    else if ((num = atoi(argv[1])) < 0 || num > MAX_CLIENTS)
    {
        fprintf(stderr, "clients limit = %d \n", MAX_CLIENTS);
        return -1;
    }

    /* SDLの初期化 */
    if (SDL_Init(SDL_INIT_TIMER))
    {
        fprintf(stderr, "Error --> SDL_Init()\n");
        return -1;
    }

    NetworkManager::init();

    while (1)
    {
    }

    NetworkManager::disconnect();

    return 0;
}