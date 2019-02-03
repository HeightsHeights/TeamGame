#include "./teamStatus.h"

TeamStatus::TeamStatus()
{
    hp = MAX_TEAM_HP;
    for (int i = 0; i < BUFF_NUMBER; i++)
    {
        buff[i] = false;
        buffTimer[i] = 0;
    }
}