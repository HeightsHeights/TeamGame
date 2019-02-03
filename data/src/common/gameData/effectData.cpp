#include "./effectData.h"

EffectData::EffectData()
{
    this->exist = false;
}
EffectData::EffectData(EFFECT_ID id, Vector3f position, unsigned int maxSpriteNum, int span)
{
    this->exist = true;
    this->id = id;
    this->position = position;
    this->maxSpriteNum = maxSpriteNum;
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