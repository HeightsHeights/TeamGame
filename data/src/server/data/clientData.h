#pragma once

#include "../../common/gameData/teamId.h"
#include "../../common/controllerParam/controllerParam.h"

class ClientData
{
private:
public:
  TEAM_ID teamId;
  char name[256];
  ControllerParam controllerParam;
};