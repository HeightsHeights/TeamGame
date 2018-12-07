#pragma once

#include "./objRawModel.h"
#include <fstream>

#define GL_GLEXT_PROTOTYPES 1
#include <GL/gl.h>
#include <GL/glut.h>
class ObjModelLoader
{
private:
  ObjRawModel *ret;

public:
  ObjModelLoader();
  ObjRawModel *load(const std::string dirPath, const std::string fileName);
};