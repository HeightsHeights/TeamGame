#pragma once

#include "./resultData.h"

#define MAX_TEAM_HP 999

typedef enum {
    BUFF_ATK = 0,
    BUFF_HP = 1,
    BUFF_SPEED = 2,
    BUFF_NUMBER = 3,
} BUFF_ID;

class TeamStatus
{
  private:
  public:
    TeamStatus();

    unsigned int hp;
    bool buff[BUFF_NUMBER];
    RESULT_ID result;
};