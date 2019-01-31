#include "./gameObjectStatus.h"

GameObjectStatus::GameObjectStatus()
{
}
GameObjectStatus::GameObjectStatus(Transform *transform, Collider *collider)
{
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
  return CObjectData();
}