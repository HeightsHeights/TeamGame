#pragma once

#include "../baseGuiLoader.h"
#include "./guiText.h"

#include <SDL2/SDL_ttf.h>

typedef enum {
  FID_NORMAL = 0,
  FID_NUM = 1,
} FONT_ID;

class GuiTextLoader : public BaseGuiLoader
{
private:
  static TTF_Font *font[FID_NUM];

public:
  static bool init();
  GuiTextLoader();
  GuiText *load(FONT_ID id, const char *string, SDL_Color color);
};