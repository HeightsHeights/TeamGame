#pragma once

#include <functional>
#include <vector>
#define GL_GLEXT_PROTOTYPES 1
#include <GL/gl.h>
#include <GL/glut.h>
#include "./pData.h"
#include "../../../common/math/touple/touple2f.h"
#include "../../../common/math/vector/vector3f.h"

class Particle
{
private:
  GLuint vao;
  GLuint texId;

  GLuint vboIndex;
  GLuint vboVertex;
  GLuint vboUv;
  GLuint vboPos;
  Touple2f spriteMaxNum;

  std::vector<PData> pData;

  void storeData(unsigned int maxnum);

  GLuint createArrayBuffer();

  void bindVao();
  void unbindVao();

  void bindTexture();
  void unbindTexture();

  void update();

public:
  Vector3f emitterPos;

  Particle();
  Particle(GLuint texId, unsigned int maxnum);
  void generate(unsigned int num);
  int draw(float brightness);
  void setSpriteNum(Touple2f spriteMaxNum);
};