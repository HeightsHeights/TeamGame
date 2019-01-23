#include "./objTextureLoader.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

bool ObjTextureLoader::load(std::string fileName, GLuint *texId)
{
    SDL_Surface *surface = IMG_Load((this->dirPath + fileName).c_str());
    if (surface == NULL)
    {
        fprintf(stderr, "Error --> loadTextureFile(%s)\n", fileName.c_str());
        return false;
    }

    int Mode = GL_RGB;
    if (surface->format->BytesPerPixel == 4)
    {
        Mode = GL_RGBA;
    }

    glGenTextures(1, texId);
    glBindTexture(GL_TEXTURE_2D, *texId);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODELVIEW);
    glTexImage2D(GL_TEXTURE_2D, 0, Mode, surface->w, surface->h, 0, Mode, GL_UNSIGNED_BYTE, surface->pixels);

    glBindTexture(GL_TEXTURE_2D, 0);
    SDL_FreeSurface(surface);
    return true;
}