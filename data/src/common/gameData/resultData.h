#pragma once

typedef enum
{
    RESULT_WIN = 0,
    RESULT_LOSE = 1,
    RESULT_NUMBER = 2,
} RESULT_ID;

class GameResult
{
  private:
  public:
    GameResult();

    bool result[RESULT_NUMBER];
};