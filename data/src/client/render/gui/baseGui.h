#pragma once

#include "./guiRect.h"
#include "./guiFlip.h"

#define GL_GLEXT_PROTOTYPES 1
#include <GL/gl.h>
#include <GL/glut.h>

class BaseGui
{
private:
  GLuint vao;
  GLuint texId;

public:
  void draw();
  void draw(GuiRect *srcRect, GuiRect *dstRect);

protected:
  BaseGui();
  BaseGui(GLuint texId);
};