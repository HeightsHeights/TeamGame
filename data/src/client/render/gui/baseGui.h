#pragma once

#define GL_GLEXT_PROTOTYPES 1
#include <GL/gl.h>
#include <GL/glut.h>

#include <SDL2/SDL.h>

#include "../../../common/math/vector/vectorSet.h"
class BaseGui
{
private:
  GLuint texId;
  GLuint vao;

public:
  BaseGui();
  void draw(Vector2f pos);

protected:
  SDL_Surface *surface;
  void bindTexture();
};