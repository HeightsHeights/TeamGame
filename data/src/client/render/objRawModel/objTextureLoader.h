#pragma once
#include <fstream>
#define GL_GLEXT_PROTOTYPES 1
#include <GL/gl.h>
#include <GL/glut.h>

class ObjTextureLoader
{
private:
  std::string dirPath;

public:
  ObjTextureLoader() {}
  ObjTextureLoader(std::string dirPath) { this->dirPath = dirPath; }
  bool load(std::string fileName, GLuint *texId);
};