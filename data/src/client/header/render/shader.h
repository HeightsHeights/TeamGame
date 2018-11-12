#pragma once

#define GL_GLEXT_PROTOTYPES 1

/******************************************************************************
 * シェーダ関係に必要なヘッダーの読み込み
******************************************************************************/
#include <GL/gl.h>
#include <GL/glut.h>
#include <fstream>

typedef enum {
  SID_STATIC = 0,
  SID_TEST = 1,
  SID_NUM = 2,
} SHADER_ID;

/******************************************************************************
 * class ShaderProgram
 * 機能1：シェーダIDなどを保持
 * 機能2：シェーダ開始関数 startShader()
 * 機能3：シェーダ終了関数 stopShader()
******************************************************************************/
class ShaderProgram
{
private:
  GLuint programID;
  GLuint vertexShaderID;
  GLuint fragmentShaderID;

public:
  ShaderProgram();
  ShaderProgram(GLuint programID, GLuint vertexShaderID, GLuint fragmentShaderID);
  void startShader();
  void stopShader();
};

/******************************************************************************
 * class BaseShaderLoader
 * 機能1：シェーダプログラムを読み込む
 * 機能2：シェーダの種類に応じて子クラスが分岐
******************************************************************************/
class BaseShaderLoader
{
private:
  GLuint programID;
  GLuint vertexShaderID;
  GLuint fragmentShaderID;

  GLuint loadShader(const char *file, int type);
  virtual void bindAttributes() = 0;

public:
  ShaderProgram *generateShader(const char *vertex_filename, const char *fragment_filename);

protected:
  void bindAttribute(int attribute, const char *variableName);
};

/******************************************************************************
 * class StaticShaderLoader
 * 機能1：StaticShader用のAttribute変数設定をする
******************************************************************************/
class StaticShaderLoader : public BaseShaderLoader
{
private:
  void bindAttributes();

public:
};
/******************************************************************************
 * class TestShaderLoader
 * 機能1：TestShader用のAttribute変数設定をする
******************************************************************************/
class TestShaderLoader : public BaseShaderLoader
{
private:
  void bindAttributes();

public:
};

/******************************************************************************
 * class ShaderManager
 * 機能1：シェーダの初期化
 * 呼び出しや終了処理の中継
******************************************************************************/
class ShaderManager
{
private:
  static ShaderProgram *shaders[SID_NUM];

public:
  static bool initShader();
  static void startShader(SHADER_ID sid);
  static void stopShader(SHADER_ID sid);
};
