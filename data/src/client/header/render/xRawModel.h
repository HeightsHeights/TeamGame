#pragma once

#define OBJ_BUFFER_LENGTH 128
#define BUFFER_OFFSET(bytes) ((GLubyte *)NULL + (bytes))
/******************************************************************************
 * Xモデル関係に必要なヘッダーの読み込み
******************************************************************************/
#include "../../../common/header/vector.h"
#include "../../../common/header/quat.h"

#include <stdio.h>
#include <vector>
#include <fstream>

#define GL_GLEXT_PROTOTYPES 1
#include <GL/gl.h>
#include <GL/glut.h>

class XRawModel
{
  private:
  public:
    XRawModel();
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