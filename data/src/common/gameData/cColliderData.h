#pragma once

#include "../../common/object/transform.h"

typedef enum {
    COLLIDER_OBB = 0,
    COLLIDER_SPHERE = 1,
    COLLIDER_NUMBER = 2,
} COLLIDER_ID;

class CColliderData
{
  private:
  public:
    COLLIDER_ID id;
    Transform transform;

    CColliderData();
    CColliderData(COLLIDER_ID id, Transform transform);
};