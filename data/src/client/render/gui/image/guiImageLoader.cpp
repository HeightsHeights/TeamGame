#include "./guiImageLoader.h"
#include <SDL2/SDL_image.h>
GuiImageLoader::GuiImageLoader()
{
}
GuiImage *GuiImageLoader::load(const char *filePath)
{
    surface = IMG_Load(filePath);
    if (surface == NULL)
    {
        fprintf(stderr, "Error --> loadTextureFile(%s)\n", filePath);
        return NULL;
    }
    GLuint texId = bindTexture();
    Vector2f textureSize(surface->w, surface->h);
    freeSurface();
    return new GuiImage(texId, textureSize);
}