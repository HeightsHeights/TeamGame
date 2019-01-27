#include "./gameObject.h"
#include <iostream>

GameObject::GameObject()
{
}
GameObject::GameObject(Transform *transform)
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

void GameObject::clearTransform()
{
  this->transform = this->initTransform;
}
bool GameObject::isCollision()
{
}