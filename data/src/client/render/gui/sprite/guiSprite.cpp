#include "./guiSprite.h"
GuiSprite::GuiSprite()
{
}
GuiSprite::GuiSprite(GLuint texId)
{
}
GuiSprite::GuiSprite(GLuint texId, Vector2f textureSize) : BaseGui(texId, textureSize)
{
}
GuiSprite::~GuiSprite()
{
}
void GuiSprite::setSpriteNum(Touple2f spriteMaxNum)
{
    this->spriteMaxNum = spriteMaxNum;
}
void GuiSprite::draw(const unsigned int spriteNum, GuiRect *dstRect)
{
    draw(spriteNum, dstRect, 1.0f);
}
void GuiSprite::draw(const unsigned int spriteNum, GuiRect *dstRect, float brightness)
{
    Vector2f textureSize = getTextureSize();
    int rowNum = spriteNum % (int)spriteMaxNum.x;
    int lineNum = spriteNum / (int)spriteMaxNum.x;
    Vector2f spriteSize = Vector2f(textureSize.x / spriteMaxNum.x, textureSize.y / spriteMaxNum.y);
    GuiRect srcRect = GuiRect(rowNum * spriteSize.x, lineNum * spriteSize.y, spriteSize.x, spriteSize.y);
    BaseGui::draw(&srcRect, dstRect, brightness);
}
void GuiSprite::draw(const unsigned int spriteNum, GuiRect *dstRect, float brightness, Vector3f pos)
{
    Vector2f textureSize = getTextureSize();
    int rowNum = spriteNum % (int)spriteMaxNum.x;
    int lineNum = spriteNum / (int)spriteMaxNum.x;
    Vector2f spriteSize = Vector2f(textureSize.x / spriteMaxNum.x, textureSize.y / spriteMaxNum.y);
    GuiRect srcRect = GuiRect(rowNum * spriteSize.x, lineNum * spriteSize.y, spriteSize.x, spriteSize.y);
    BaseGui::draw(&srcRect, dstRect, brightness, pos);
}