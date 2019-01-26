#include "./gameObject.h"
#include "../render/objRawModel/objModelLoader.h"

GameObject::GameObject()
{
}
GameObject::GameObject(const std::string dirPath, const std::string fileName, Transform *transform)
{
  if (transform == NULL)
  {
    this->transform.position = Vector3f_ZERO;
    this->transform.rotation = Vector3f_ZERO;
    this->transform.scale = Vector3f(1.0f, 1.0f, 1.0f);
  }
  else
  {
    this->transform.position = transform->position;
    this->transform.rotation = transform->rotation;
    this->transform.scale = transform->scale;
  }

  model = ObjModelLoader().load("", "");
}

void GameObject::draw()
{
  glPushMatrix();

  glScalef(transform.scale.x, transform.scale.y, transform.scale.z);
  glRotatef(transform.rotation.y, 0.0f, 1.0f, 0.0f);
  glTranslatef(transform.position.x, transform.position.y, transform.position.z);

  model->draw();
  glPopMatrix();
}