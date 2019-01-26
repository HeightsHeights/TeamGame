#include "./particleLoader.h"
#include <SDL2/SDL_image.h>
ParticleLoader::ParticleLoader()
{
}
Particle *ParticleLoader::load(const char *filePath, const unsigned int horizontallyNum, const unsigned int verticallyNum, unsigned int maxnum)
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
    Particle *ret = new Particle(texId, maxnum);
    ret->setSpriteNum(Touple2f(horizontallyNum, verticallyNum));

    freeSurface();
    return ret;
}