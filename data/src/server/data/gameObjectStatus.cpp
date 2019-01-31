#include "./gameObjectStatus.h"
#include <iostream>

GameObjectStatus::GameObjectStatus()
{
}
GameObjectStatus::GameObjectStatus(Transform *transform)
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
}

void GameObjectStatus::clearTransform()
{
  this->transform = this->initTransform;
}
