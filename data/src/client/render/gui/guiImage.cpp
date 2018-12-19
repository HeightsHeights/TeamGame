#include "./guiImage.h"
#include <SDL2/SDL_image.h>

GuiImage::GuiImage()
{
}
GuiImage::GuiImage(const char *filePath) : BaseGui()
{
    surface = IMG_Load(filePath);
    if (surface == NULL)
    {
        fprintf(stderr, "Error --> loadTextureFile(%s)\n", filePath);
    }
    else
    {
        bindTexture();
    }
}