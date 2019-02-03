#include "./effect.h"

Effect::Effect()
{
    this->exist = false;
}
Effect::Effect(EFFECT_ID id, Vector3f position, unsigned int maxSpriteNum, int span)
{
    this->exist = true;
    this->id = id;
    this->position = position;
    this->maxSpriteNum = maxSpriteNum;
    this->counter = RingCounter(0, 0, span);
    this->currentSpriteNum = 0;
}
void Effect::update()
{
    ++counter;
    if (counter.isMax())
    {
        currentSpriteNum++;
        if (currentSpriteNum > maxSpriteNum)
        {
            this->exist = false;
        }
    }
}
EFFECT_ID Effect::getId()
{
    return this->id;
}
unsigned int Effect::getSpriteNum()
{
    return this->currentSpriteNum;
}