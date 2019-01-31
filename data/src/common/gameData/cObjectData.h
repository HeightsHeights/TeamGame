#pragma once

#include "../../common/object/transform.h"

#define MAX_STATIC_OBJECTS 8
#define MAX_DYNAMIC_OBJECTS 100

typedef enum {
  OBJECT_TILE = 0,
  OBJECT_SKYBOX = 1,
  OBJECT_WALL = 2,
  OBJECT_TOWER = 3,
  OBJECT_BOMB = 4,
  OBJECT_NUMBER = 5,
} OBJECT_ID;

class CObjectData
{
private:
public:
  CObjectData();
  OBJECT_ID objectId;
  Transform transform;
};