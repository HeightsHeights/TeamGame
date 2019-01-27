#include "./character.h"

Character::Character()
{
}
Character::Character(const std::string dirPath, const std::string fileName, Transform *transform)
{
    speed = 0.1f;

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
    hands[HAND_RIGHT]->transform.position = Vector3f(1.5f, 1.5f, 0.0f);
    hands[HAND_LEFT]->transform.position = Vector3f(-1.5f, 1.5f, 0.0f);
    mainBody = new GameObject(dirPath, fileName, NULL);
}

void Character::move(Vector3f moveDirection)
{
    moveDirection = moveDirection.normalize();

    if (moveDirection.x != 0 || moveDirection.y != 0 || moveDirection.z != 0)
    {
        lookingDirection = moveDirection;
    }

    transform.position += moveDirection * speed;
}

void Character::motion(ATTACK_ID id, int time)
{
}

void Character::draw()
{
    glPushMatrix();

    glScalef(transform.scale.x, transform.scale.y * 2, transform.scale.z);
    glTranslatef(transform.position.x, transform.position.y, transform.position.z);
    lookatDir(lookingDirection);

    glPushMatrix();
    glTranslatef(hands[HAND_RIGHT]->transform.position.x, hands[HAND_RIGHT]->transform.position.y, hands[HAND_RIGHT]->transform.position.z);
    hands[HAND_RIGHT]->draw();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(hands[HAND_LEFT]->transform.position.x, hands[HAND_LEFT]->transform.position.y, hands[HAND_LEFT]->transform.position.z);
    hands[HAND_LEFT]->draw();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(mainBody->transform.position.x, mainBody->transform.position.y, mainBody->transform.position.z);
    mainBody->draw();
    glPopMatrix();

    glPopMatrix();
}

void Character::lookatDir(Vector3f direction)
{
    direction.y = 0;

    Vector3f vecY = Vector3f(0, 1, 0);
    Vector3f vecZ = Vector3f(0, 0, 1);

    float theta = direction.betweenAngleDegree(vecZ);
    if (Vector3f::cross(vecZ, direction).y < 0)
    {
        theta *= -1;
    }
    glRotated(theta, vecY.x, vecY.y, vecY.z);
}
