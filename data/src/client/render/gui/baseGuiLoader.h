#pragma once

#include <GL/gl.h>
#include <SDL2/SDL.h>

class BaseGuiLoader
{
private:
public:
protected:
  SDL_Surface *surface;

  BaseGuiLoader();
  GLuint bindTexture();
  void freeSurface();
};