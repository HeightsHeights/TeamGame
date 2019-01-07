#include "./guiSprite.h"
GuiSprite::GuiSprite()
{
}
GuiSprite::GuiSprite(GLuint texId) : BaseGui(texId)
{
}
void GuiSprite::setSurfaceSize(Vector2f surfaceSize)
{
    this->surfaceSize = surfaceSize;
}
void GuiSprite::setSpriteNum(Touple2f spriteNum)
{
    this->spriteNum = spriteNum;
}