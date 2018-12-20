#pragma once

#define GL_GLEXT_PROTOTYPES 1
#include <GL/gl.h>
#include <GL/glut.h>
#include <vector>

#include "../../../common/math/vector/vectorSet.h"

class GuiDataBinder
{
private:
  GLuint createVao();
  void storeAttributeData(const int attributeNumber, const int num, const GLsizeiptr size, const float *data);
  void bindIndicesBuffer(const GLsizeiptr size, const unsigned int *indices);
  void unbindVao();

public:
  GLuint dataBind(std::vector<unsigned int> vertexIndices, std::vector<Vector3f> vertexPositions, Vector2f vertexUvs[], Vector3f vertexNormals[]);
};