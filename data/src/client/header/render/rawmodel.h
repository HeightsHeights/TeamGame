#pragma once

/******************************************************************************
 * OBJモデル関係に必要なヘッダーの読み込み
******************************************************************************/
#include "../header/vector.h"

#include <stdio.h>
#include <vector>

#define GL_GLEXT_PROTOTYPES 1
#include <GL/gl.h>
#include <GL/glut.h>

/******************************************************************************
 * class RawModel
 * 機能1：vaoバッファーの情報と頂点個数を保持する
 * 機能2：描画関数 drawModel()
******************************************************************************/
class RawModel
{
private:
  GLuint vertexArrayObject;
  unsigned int vertexCount;

public:
  RawModel();
  RawModel(GLuint vao, unsigned int vertexCount);
  void drawModel();
};

/******************************************************************************
 * class ModelLoader
 * 機能1：ファイルを読み込んでRawModelデータとして返す
******************************************************************************/
class ModelLoader
{
private:
  GLuint vao;
  unsigned int vertexCount;
  bool loadOBJFile(const char *filename);

public:
  RawModel loadFile(const char *filename);
};