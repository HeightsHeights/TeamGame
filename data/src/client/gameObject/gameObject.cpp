#include "./gameObject.h"
#include "../render/objRawModel/objModelLoader.h"

GameObject::GameObject()
{
}
GameObject::GameObject(const std::string dirPath, const std::string fileName, Transform *transform)
{
  if (transform == NULL)
  {
    this->initTransform.position = this->transform.position = Vector3f_ZERO;
    this->initTransform.rotation = this->transform.rotation = Vector3f_ZERO;
    this->initTransform.scale = this->transform.scale = Vector3f(1.0f, 1.0f, 1.0f);
  }
  else
  {
    this->initTransform.position = this->transform.position = transform->position;
    this->initTransform.rotation = this->transform.rotation = transform->rotation;
    this->initTransform.scale = this->transform.scale = transform->scale;
  }

  model = ObjModelLoader().load(dirPath, fileName);
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