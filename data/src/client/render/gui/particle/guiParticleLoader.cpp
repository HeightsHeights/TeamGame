#include "./guiParticleLoader.h"
#include <SDL2/SDL_image.h>
GuiParticleLoader::GuiParticleLoader()
{
}
GuiParticle *GuiParticleLoader::load(const char *filePath, unsigned int count)
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
    return new GuiParticle(texId, textureSize);
}