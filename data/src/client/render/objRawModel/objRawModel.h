#pragma once

#define MAX_MATERIAL_NAME 128
/******************************************************************************
 * OBJモデル関係に必要なヘッダーの読み込み
******************************************************************************/
#include "../../../common/math/vector/vectorSet.h"

#include <vector>
#include <fstream>

#define GL_GLEXT_PROTOTYPES 1
#include <GL/gl.h>
#include <GL/glut.h>

class ObjSubset
{
private:
  unsigned int vertexCount;
  unsigned int materialId;

public:
  ObjSubset();
  ObjSubset(unsigned int vertexCount, unsigned int materialId);
  unsigned int getVertexCount() { return this->vertexCount; }
  int getMaterialId() { return this->materialId; }
};
class ObjMaterial
{
private:
  char name[MAX_MATERIAL_NAME];
  Touple4f ambient;
  Touple4f diffuse;
  Touple4f specular;
  Touple4f emissive;
  float power;
  GLuint texId;

public:
  ObjMaterial();
  ObjMaterial(char *name, Touple4f ambient, Touple4f diffuse, Touple4f specular, Touple4f emissive, float power, GLuint texId);
  bool isEqualName(const char *name);
  void applyMaterial();
  void applyTexture();
};
class ObjRawModel
{
private:
  GLuint vao;
  std::vector<ObjSubset> subsets;
  std::vector<ObjMaterial> materials;

public:
  ObjRawModel();
  void setVao(GLuint vao);
  void pushSubset(const ObjSubset subset);
  void pushMaterial(const ObjMaterial material);
  unsigned int getMtlId(const char *mName);
  void draw();
};