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

  GLuint vboVertex;
  GLuint vboUv;
  GLuint vboIndex;

  Vector2f textureSize;

  void storeData();

  void bindVao();
  void unbindVao();

  void bindTexture();
  void unbindTexture();

public:
  void draw();
  void draw(GuiRect *srcRect, GuiRect *dstRect);
  Vector2f getTextureSize();

protected:
  BaseGui();
  BaseGui(GLuint texId);
  BaseGui(GLuint texId, Vector2f textureSize);
  virtual ~BaseGui();
};