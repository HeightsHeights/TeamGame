#pragma once

#include <SDL2/SDL_ttf.h>

#include "./baseGui.h"

typedef enum {
    FID_NORMAL = 0,
    FID_NUM = 1,
} FONT_ID;

class GuiString : public BaseGui
{
  private:
    static TTF_Font *font[FID_NUM];

  public:
    static bool init();
    GuiString();
    GuiString(FONT_ID id, const char *string, SDL_Color color);
};