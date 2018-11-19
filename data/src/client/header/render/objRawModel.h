#pragma once

#define MAX_MATERIAL_NAME 128
#define BUFFER_OFFSET(bytes) ((GLubyte *)NULL + (bytes))
/******************************************************************************
 * OBJモデル関係に必要なヘッダーの読み込み
******************************************************************************/
#include "../../../common/header/vector.h"
#include "../../../common/header/quat.h"

#include <stdio.h>
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

public:
  ObjMaterial();
  ObjMaterial(char *name, Touple4f ambient, Touple4f diffuse, Touple4f specular, Touple4f emissive, float power);
  bool isEqualName(const char *name);
  void applyMaterial();
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
class ObjModelLoader
{
private:
  std::vector<Vector3f> vertices;
  std::vector<Vector2f> textures;
  std::vector<Vector3f> normals;

  std::vector<unsigned int> indices;
  std::vector<unsigned int> textureIndices;
  std::vector<unsigned int> normalIndices;
  ObjRawModel *ret;

  bool loadObjFile(const char *filename);
  void createSubset(std::ifstream *file);
  GLuint createVao();
  void storeAttributeData(const int attributeNumber, const GLsizeiptr size, const float *data, GLboolean normalize);
  void bindIndicesBuffer(const GLsizeiptr size, const unsigned int *indices);
  void unbindVao();
  bool loadMtlFile(const char *filename);
  void createMaterial(std::ifstream *file);

public:
  ObjModelLoader();
  ObjRawModel *load(const char *objFilename, const char *mtlFilename);
};