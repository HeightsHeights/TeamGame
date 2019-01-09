#pragma once

#include <GL/gl.h>

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
  GLuint getProgramId();
};
