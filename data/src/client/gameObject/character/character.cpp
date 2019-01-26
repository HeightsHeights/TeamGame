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
        hands[i] = new GameObject("./data/res/gui/obj/", "hand", NULL);
    }
    mainBody = new GameObject(dirPath, fileName, NULL);
}

void Character::move(Vector2f movepoint)
{
    transform.position.x = movepoint.x;
    transform.position.z = movepoint.y;
}

void Character::draw()
{
    glPushMatrix();

    glScalef(transform.scale.x, transform.scale.y, transform.scale.z);
    glRotatef(transform.rotation.y, 0.0f, 1.0f, 0.0f);
    glTranslatef(transform.position.x, transform.position.y, transform.position.z);

    glPushMatrix();
    glTranslatef(3.5f, 2.0f, 0.0f);
    hands[HAND_RIGHT]->draw();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-3.5f, 2.0f, 0.0f);
    hands[HAND_LEFT]->draw();
    glPopMatrix();

    mainBody->draw();

    glPopMatrix();
}