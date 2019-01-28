#include "./character.h"
#include <math.h>
Character::Character()
{
}
Character::Character(const std::string dirPath, const std::string fileName, Transform *transform)
{
    speed = 0.1f;

    if (transform == NULL)
    {
        this->transform = Transform();
    }
    else
    {
        this->transform = *transform;
    }

    Transform handInitTramsform[HAND_NUMBER] = {
        Transform(Vector3f(1.5f, 1.5f, 0.0f), Vector3f_ZERO, Vector3f(1.0f, 1.0f, 1.0f)),
        Transform(Vector3f(-1.5f, 1.5f, 0.0f), Vector3f_ZERO, Vector3f(1.0f, 1.0f, 1.0f)),
    };
    for (int i = HAND_RIGHT; i < HAND_NUMBER; i++)
    {
        hands[i] = new GameObject("./data/res/gui/obj/", "hand", &handInitTramsform[i]);
    }
    mainBody = new GameObject(dirPath, fileName, NULL);

    lookingDirection = Vector3f(1.0f, 0.0f, 0.0f);
    weapon = NULL;
}

void Character::move(Vector3f moveDirection)
{
    moveDirection = moveDirection.normalize();

    if (moveDirection != Vector3f_ZERO)
    {
        lookingDirection = moveDirection;
    }

    transform.position += moveDirection * speed;
}

void Character::motion(MOTION_ID id, int time)
{
    switch (id)
    {
    case MOTION_ATTACK:
        //weaponSodo(time);
        weaponAx(time);
        //weaponBamboo(time);
        //weaponHit(time);
        break;
    case MOTION_THROW:
        weaponThrow(time);
        break;
    case MOTION_NULL:
        Cancel();
        break;
    }
}

void Character::draw()
{
    glPushMatrix();

    glScalef(transform.scale.x * 1.5, transform.scale.y * 3, transform.scale.z * 1.5);
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

    if (weapon != NULL)
    {
        glPushMatrix();
        glTranslatef(weapon->transform.position.x, weapon->transform.position.y, weapon->transform.position.z);
        mainBody->draw();
        glPopMatrix();
    }

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

void Character::weaponSodo(int time)
{
    hands[HAND_LEFT]->transform.position += Vector3f(0.0f, 0.1f * (float)cos(270 + (time / 10)), 0.1f * (float)sin(270 + (time / 10)));
}
void Character::weaponAx(int time)
{
    hands[HAND_LEFT]->transform.position += Vector3f(0.1f * (float)sin(time / 10), 0.0f, 0.1f * (float)cos(time / 10));
}
void Character::weaponBamboo(int time)
{
    if (time % 2 == 0)
    {
        hands[HAND_LEFT]->transform.position += Vector3f(0.0f, 0.0f, 1.0f);
    }
    else
    {
        hands[HAND_LEFT]->transform.position -= Vector3f(0.0f, 0.0f, 1.0f);
    }
}
void Character::weaponHit(int time)
{
    hands[HAND_LEFT]->transform.position += Vector3f(0.1f * (float)sin(time / 10), 0.0f, 0.1f * (float)cos(time / 10));
}

void Character::weaponThrow(int time)
{
    hands[HAND_LEFT]->transform.position += Vector3f(0.0, (float)sin(time), (float)cos(time));
}

void Character::Cancel()
{
    hands[HAND_RIGHT]->clearTransform();
    hands[HAND_LEFT]->clearTransform();
}