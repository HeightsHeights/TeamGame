#include "./gameObjectStatus.h"

GameObjectStatus::GameObjectStatus()
{
}
GameObjectStatus::GameObjectStatus(Transform *transform, Collider *collider)
{
  this->objectId = OBJECT_NUMBER;
  if (transform == NULL)
  {
    this->transform = Transform();
  }
  else
  {
    this->transform = *transform;
  }
  this->initTransform = this->transform;

  if (collider != NULL)
  {
    this->collider = *collider;
  }
}

void GameObjectStatus::clearTransform()
{
  this->transform = this->initTransform;
}

CObjectData GameObjectStatus::getDataForClient()
{
  CObjectData ret(this->objectId, &this->transform);

  if (0 < this->collider.obbs.size())
  {
    Obb *pObb = &this->collider.obbs[0];
    ret.collider = CColliderData(COLLIDER_OBB, Transform(pObb->center, Vector3f_ZERO, Vector3f(pObb->length[0], pObb->length[1], pObb->length[2])));
  }
  else if (0 < this->collider.spheres.size())
  {
    Sphere *pSphere = &this->collider.spheres[0];
    ret.collider = CColliderData(COLLIDER_SPHERE, Transform(pSphere->center, Vector3f_ZERO, Vector3f(pSphere->radius, pSphere->radius, pSphere->radius)));
  }

  return ret;
}