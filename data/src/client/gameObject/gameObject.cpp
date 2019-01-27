#include "./gameObject.h"
#include "../render/objRawModel/objModelLoader.h"

GameObject::GameObject()
{
}
GameObject::GameObject(const std::string dirPath, const std::string fileName, Transform *transform)
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