#pragma once

#include <GL/gl.h>
#include "./shaderProgram.h"

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
  virtual void bindAttributes();

public:
  ShaderProgram *generateShader(const char *vertex_filename, const char *fragment_filename);
  virtual ~BaseShaderLoader() {}

protected:
  void bindAttribute(int attribute, const char *variableName);
  GLint getAttribute(const char *variableName);
  GLint getUniform(const char *variableName);
};

/******************************************************************************
 * class StaticShaderLoader
 * 機能1：StaticShader用のAttribute変数設定をする
******************************************************************************/
class StaticShaderLoader : public BaseShaderLoader
{
private:
  virtual void bindAttributes();

public:
};
/******************************************************************************
 * class TestShaderLoader
 * 機能1：TestShader用のAttribute変数設定をする
******************************************************************************/
class TestShaderLoader : public BaseShaderLoader
{
private:
  virtual void bindAttributes();

public:
};
/******************************************************************************
 * class GuiShaderLoader
 * 機能1：GuiShader用のAttribute変数設定をする
******************************************************************************/
class GuiShaderLoader : public BaseShaderLoader
{
private:
  virtual void bindAttributes();

public:
};