#pragma once

#define MAX_MATERIAL_NAME 128
/******************************************************************************
 * OBJモデル関係に必要なヘッダーの読み込み
******************************************************************************/
#include "../../../common/header/vector.h"
#include "../../../common/header/quat.h"

#include <stdio.h>
#include <vector>

#define GL_GLEXT_PROTOTYPES 1
#include <GL/gl.h>
#include <GL/glut.h>

class ObjSubset
{
  private:
    GLuint vao;
    unsigned int vertexCount;
    unsigned int materialId;

  public:
    ObjSubset();
    ObjSubset(GLuint vao, unsigned int vertexCount, unsigned int materialId);
    GLint getVao() { return this->vao; }
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
    std::vector<ObjSubset> subsets;
    std::vector<ObjMaterial> materials;

  public:
    ObjRawModel();
    void pushMesh(const ObjSubset subset);
    void pushMaterial(const ObjMaterial material);
    void draw();
};
class ObjModelLoader
{
  private:
    bool loadObjFile();
    bool loadMtlFile();

  public:
    ObjModelLoader();
    ObjRawModel load(const char *objFilename, const char *mtlFilename);
};