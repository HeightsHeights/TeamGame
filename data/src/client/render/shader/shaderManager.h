#pragma once

#include "./shaderProgram.h"

typedef enum {
  SID_T_PHONG = 0,
  SID_NT_PHONG = 1,
  SID_GUI = 2,
  SID_NUM = 3,
} SHADER_ID;

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
  static bool init();
  static void startShader(SHADER_ID sid);
  static void stopShader(SHADER_ID sid);
  static GLuint getProgramId(SHADER_ID sid);
};
