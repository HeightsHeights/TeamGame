#include "./effectData.h"

const unsigned int MAX_SPRITE[EFFECT_NUMBER] = {
    5,
    9,
    6,
};

EffectData::EffectData()
{
    this->exist = false;
}
EffectData::EffectData(EFFECT_ID id, Vector3f position, int span)
{
    this->exist = true;
    this->id = id;
    this->position = position;
    this->maxSpriteNum = MAX_SPRITE[id];
    this->counter = RingCounter(0, 0, span);
    this->currentSpriteNum = 0;
}
void EffectData::update()
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
EFFECT_ID EffectData::getId()
{
    return this->id;
}
unsigned int EffectData::getSpriteNum()
{
    return this->currentSpriteNum;
}