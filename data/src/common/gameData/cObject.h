#pragma once

#include "../../common/object/transform.h"

typedef enum {
  OBJECT_TITLE = 0,
  OBJECT_NUMBER = 1,
} OBJECT_ID;

class CObject
{
private:
public:
  Transform transform;
};