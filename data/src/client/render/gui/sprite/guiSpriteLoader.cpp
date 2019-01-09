#include "./guiSpriteLoader.h"
#include <SDL2/SDL_image.h>
GuiSpriteLoader::GuiSpriteLoader()
{
}
GuiSprite *GuiSpriteLoader::load(const char *filePath, const unsigned int horizontallyNum, const unsigned int verticallyNum)
{
    if (horizontallyNum == 0 || verticallyNum == 0)
    {
        fprintf(stderr, "Error --> horizontallyNum or verticallyNum = 0\n");
        return NULL;
    }

    surface = IMG_Load(filePath);
    if (surface == NULL)
    {
        fprintf(stderr, "Error --> loadTextureFile(%s)\n", filePath);
        return NULL;
    }

    GLuint texId = bindTexture();
    Vector2f textureSize(surface->w, surface->h);

    GuiSprite *ret = new GuiSprite(texId, textureSize);
    ret->setSpriteNum(Touple2f(horizontallyNum, verticallyNum));

    freeSurface();
    return ret;
}