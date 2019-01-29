#include "./resultData.h"

GameResult::GameResult()
{
    for (int i = 0; i < RESULT_NUMBER; i++)
    {
        result[i] = false;
    }
}