#pragma once

#include <GL/gl.h>
#include <SDL2/SDL.h>

#include "../../../common/math/vector/vectorSet.h"
class BaseGui
{
private:
  GLuint texId;

public:
  BaseGui();
  virtual void draw(Vector2f pos);

protected:
  SDL_Surface *surface;
  void bindTexture();
};