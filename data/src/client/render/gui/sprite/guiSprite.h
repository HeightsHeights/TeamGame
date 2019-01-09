#pragma once

#include "../baseGui.h"

class GuiSprite : BaseGui
{
private:
  Touple2f spriteMaxNum;

public:
  GuiSprite();
  GuiSprite(GLuint texId);
  GuiSprite(GLuint texId, Vector2f textureSize);
  ~GuiSprite();
  void setSpriteNum(Touple2f spriteMaxNum);
  void draw(const unsigned int spriteNum, GuiRect *dstRect);
  void draw(const unsigned int spriteNum, GuiRect *dstRect, float brightness);
};