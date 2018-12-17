#include "./shaderManager.h"
#include "./shaderLoader.h"
#include <stdio.h>
#include <fstream>

#define SHADER_DIR_PATH "./data/src/client/shaders/"
#define VERTEX_FILE_EXTENSION ".vert"
#define FRAGMENT_FILE_EXTENSION ".frag"

const std::string SHADER_NAME[SID_NUM] = {
    "staticShader",
    "testShader",
    "guiShader",
    "redShader",
};

ShaderProgram *ShaderManager::shaders[SID_NUM];

/******************************************************************************
 * ShaderManager
******************************************************************************/
//シェーダ初期化
bool ShaderManager::init()
{

    BaseShaderLoader *loaders[SID_NUM] = {
        new StaticShaderLoader(),
        new TestShaderLoader(),
        new GuiShaderLoader(),
        new RedShaderLoader(),
    };

    for (int i = 0; i < SID_NUM; i++)
    {
        std::string vertexPath = SHADER_DIR_PATH + SHADER_NAME[i] + VERTEX_FILE_EXTENSION;
        std::string fragmentPath = SHADER_DIR_PATH + SHADER_NAME[i] + FRAGMENT_FILE_EXTENSION;
        shaders[i] = loaders[i]->generateShader(vertexPath.c_str(), fragmentPath.c_str());
        if (shaders[i] == NULL)
        {
            fprintf(stderr, "Error --> shader[%d] is NULL\n", i);
            return false;
        }
        delete loaders[i];
    }

    return true;
}
//シェーダを始める
void ShaderManager::startShader(SHADER_ID sid)
{
    shaders[sid]->startShader();
}
//シェーダを終わらせる
void ShaderManager::stopShader(SHADER_ID sid)
{
    shaders[sid]->stopShader();
}