#pragma once

#include <iostream>
#include "../../common/object/transform.h"
#include "./cColliderData.h"

#define MAX_DYNAMIC_OBJECTS 50

typedef enum
{
  OBJECT_TYPE_STATIC = 0,
  OBJECT_TYPE_DYNAMIC = 1,
  OBJECT_TYPE_NUMBER = 2,
} OBJECT_TYPE;

typedef enum
{
  OBJECT_SKYBOX = 0,        //<-staticObject
  OBJECT_TILE = 1,          //
  OBJECT_TOWER_R = 2,       //
  OBJECT_TOWER_B = 3,       //
  OBJECT_WALL_R = 4,        //
  OBJECT_WALL_B = 5,        //
  OBJECT_WALL_NORMAL = 6,   //
  OBJECT_BOMB = 7,          //<-dynamicObject
  OBJECT_JEWEL_R = 8,       //
  OBJECT_JEWEL_G = 9,       //
  OBJECT_JEWEL_B = 10,      //
  OBJECT_MUSH = 11,         //<-chara
  OBJECT_BAMBOO = 12,       //
  OBJECT_CHARA_HAND = 13,   //
  OBJECT_DEBUG_OBB = 14,    //<-debug
  OBJECT_DEBUG_SPHERE = 15, //
  OBJECT_NUMBER = 16,       //
} OBJECT_ID;

typedef enum
{
  SOBJECT_TILE = 0,
  SOBJECT_TOWER_R = 1,
  SOBJECT_TOWER_B = 2,
  SOBJECT_WALL_R1 = 3,
  SOBJECT_WALL_R2 = 4,
  SOBJECT_WALL_B1 = 5,
  SOBJECT_WALL_B2 = 6,
  SOBJECT_WALL_NORMAL = 7,
  SOBJECT_NUMBER = 8,
} STATIC_OBJECT_ID;

class CObjectData
{
private:
public:
  CObjectData();
  CObjectData(OBJECT_ID id, bool exist);
  CObjectData(OBJECT_ID id, bool exist, Transform *transform);

  bool exist;
  OBJECT_ID objectId;
  Transform transform;
  // CColliderData collider;
};