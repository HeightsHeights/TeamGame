#pragma once

#define OBJ_BUFFER_LENGTH 128
#define BUFFER_OFFSET(bytes) ((GLubyte *)NULL + (bytes))
/******************************************************************************
 * Xモデル関係に必要なヘッダーの読み込み
******************************************************************************/
#include "../../../common/math/vector/vectorSet.h"

#include <stdio.h>
#include <vector>
#include <fstream>

#define GL_GLEXT_PROTOTYPES 1
#include <GL/gl.h>
#include <GL/glut.h>

class VertexData
{

private:
  Vector3f pos;
  Vector2f uv;
  Vector3f normal;

public:
  VertexData(Vector3f pos, Vector2f uv, Vector3f normal)
  {
    this->pos = pos;
    this->uv = uv;
    this->normal = normal;
  }
  VertexData(Vector3f pos, Vector3f normal)
  {
    this->pos = pos;
    this->normal = normal;
  }
};

class XRawModel
{
private:
  GLuint vao;
  std::vector<unsigned int> vertexCount;

public:
  XRawModel();
  void setVao(GLuint vao);
  void pushVertexCount(unsigned int vertexCount);
  void draw();
};

class XModelLoader
{
private:
  std::vector<Vector3f> vertices;
  std::vector<Vector2f> textures;
  std::vector<Vector3f> normals;

  std::vector<unsigned int> indices;
  std::vector<unsigned int> textureIndices;
  std::vector<unsigned int> normalIndices;

  XRawModel *ret;

  std::ifstream file;
  unsigned int maxFile;

  unsigned int numVertex;
  unsigned int numNormal;

  bool skipLine();
  bool loadXFile();
  GLuint createVao();
  void storeAttributeData(const int attributeNumber, const GLsizeiptr size, const float *data, GLboolean normalize);
  void bindIndicesBuffer(const GLsizeiptr size, const unsigned int *indices);
  void unbindVao();

public:
  XModelLoader();
  XRawModel *load(const char *fileName);
};