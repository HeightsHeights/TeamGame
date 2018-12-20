#pragma once

#include "../baseGuiLoader.h"
#include "./guiSprite.h"

class GuiSpriteLoader : public BaseGuiLoader
{
private:
public:
  GuiSpriteLoader();
  GuiSprite *load(const char *filePath);
};