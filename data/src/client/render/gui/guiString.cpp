#include "./guiString.h"

#include <fstream>

#define FONT_DIR_PATH "./data/res/gui/fonts/"
#define TTFFILE_EXTENSION ".ttf"

TTF_Font *GuiString::font[FID_NUM];

const std::string FONT_NAME[FID_NUM] =
    {
        "TakaoMincho",
};

bool GuiString::init()
{
    if (TTF_Init() < 0)
    {
        return false;
    }
    for (int i = 0; i < FID_NUM; i++)
    {
        std::string path = FONT_DIR_PATH + FONT_NAME[i] + TTFFILE_EXTENSION;
        font[i] = TTF_OpenFont(path.c_str(), 24);
        if (font[i] == NULL)
        {
            return false;
        }
    }
    return true;
}

GuiString::GuiString()
{
}
GuiString::GuiString(FONT_ID id, const char *string, SDL_Color color)
{
    if (id < FID_NUM)
    {
        surface = TTF_RenderUTF8_Blended(font[id], string, color);
        bindTexture();
    }
}