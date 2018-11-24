#pragma once

#include "./shaderProgram.h"

typedef enum
{
    SID_STATIC = 0,
    SID_TEST = 1,
    SID_NUM = 2,
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
    static bool initShader();
    static void startShader(SHADER_ID sid);
    static void stopShader(SHADER_ID sid);
};
