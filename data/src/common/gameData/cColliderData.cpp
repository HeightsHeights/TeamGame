
#include "cColliderData.h"
CColliderData::CColliderData()
{
}
CColliderData::CColliderData(COLLIDER_ID id, Transform transform)
{
    this->id = id;
    this->transform = transform;
}