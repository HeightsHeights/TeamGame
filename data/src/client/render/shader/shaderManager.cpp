#include "./shaderManager.h"
#include "./shaderLoader.h"
#include <stdio.h>

const char *VERTEX_FILE[SID_NUM] = {
    "./data/src/client/shader/staticVertexShader.vert",
    "./data/src/client/shader/testVertexShader.vert",
    "./data/src/client/shader/guiVertexShader.vert",
    "./data/src/client/shader/redVertexShader.vert",
    "./data/src/client/shader/partVertexShader.vert",
};

const char *FRAGMENT_FILE[SID_NUM] = {
    "./data/src/client/shader/staticFragmentShader.frag",
    "./data/src/client/shader/testFragmentShader.frag",
    "./data/src/client/shader/guiFragmentShader.frag",
    "./data/src/client/shader/redFragmentShader.frag",
    "./data/src/client/shader/partFragmentShader.frag",
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
        new PartShaderLoader(),
    };

    for (int i = 0; i < SID_NUM; i++)
    {
        shaders[i] = loaders[i]->generateShader(VERTEX_FILE[i], FRAGMENT_FILE[i]);
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