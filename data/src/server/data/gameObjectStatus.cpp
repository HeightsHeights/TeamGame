#include "./gameObjectStatus.h"
#include <iostream>

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
  if (collider == NULL)
  {
    this->collider = *collider;
  }
  this->initTransform = this->transform;
}

void GameObjectStatus::clearTransform()
{
  this->transform = this->initTransform;
}

CObjectData GameObjectStatus::getClientData()
{
}