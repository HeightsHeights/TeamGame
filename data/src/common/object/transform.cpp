#include "./transform.h"

Transform::Transform()
{
    this->scale = Vector3f(1.0f, 1.0f, 1.0f);
}
Transform::Transform(Vector3f position, Vector3f rotation, Vector3f scale)
{
    this->position = position;
    this->rotation = rotation;
    this->scale = scale;
}