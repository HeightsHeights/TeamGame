#pragma once

#include "../../common/gameData/teamData.h"
#include "../../common/controllerParam/controllerParam.h"

class ClientData
{
  private:
  public:
    TEAM_ID teamId;
    char name[256];
    ControllerParam controllerParam;
};