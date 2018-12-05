#ifdef _ENABLE_WII

#pragma once

#include "./wiiRemote.h"

class WiiRemoteConnector
{
private:
public:
  WiiRemoteConnector();
  WiiRemote *connect(const char *id);
};
#endif