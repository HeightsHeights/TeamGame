#include "./character.h"

Character::Character()
{
}
Character::Character(const std::string dirPath, const std::string fileName, Transform *transform)
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

    for (int i = HAND_RIGHT; i < HAND_NUMBER; i++)
    {
        hands[i] = new GameObject("", "", NULL);
    }
    mainBody = new GameObject(dirPath, fileName, NULL);
}

void Character::move()
{
}

void Character::draw()
{
    glPushMatrix();

    glScalef(transform.scale.x, transform.scale.y, transform.scale.z);
    glRotatef(transform.rotation.y, 0.0f, 1.0f, 0.0f);
    glTranslatef(transform.position.x, transform.position.y, transform.position.z);

    hands[HAND_RIGHT]->draw();
    hands[HAND_LEFT]->draw();
    mainBody->draw();

    glPopMatrix();
}