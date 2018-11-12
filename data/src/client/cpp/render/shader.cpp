#include "../../header/render/shader.h"
#include "../../header/render/glsl.h"
#include <stdio.h>

const char *VERTEX_FILE[SID_NUM] = {
    "./data/src/client/shader/staticVertexShader.vert",
    "./data/src/client/shader/testVertexShader.vert"};

const char *FRAGMENT_FILE[SID_NUM] = {
    "./data/src/client/shader/staticFragmentShader.frag",
    "./data/src/client/shader/testFragmentShader.frag"};

ShaderProgram *ShaderManager::shaders[SID_NUM];

/******************************************************************************
 * コンストラクタ
******************************************************************************/

/******************************************************************************
 * ShaderManager
******************************************************************************/
//シェーダ初期化
bool ShaderManager::initShader()
{
    for (int i = 0; i < SID_NUM; i++)
    {
        shaders[i] = StaticShaderLoader().generateShader(VERTEX_FILE[i], FRAGMENT_FILE[i]);
        if (shaders[i] == NULL)
        {
            fprintf(stderr, "Error --> shader[%d] is NULL\n", i);
            return false;
        }
        }
    return true;
}
//シェーダを始める
void ShaderManager::startShader(SHADER_ID sid)
{
    (*shaders[sid]).startShader();
}
//シェーダを終わらせる
void ShaderManager::stopShader(SHADER_ID sid)
{
    (*shaders[sid]).stopShader();
}
/******************************************************************************
 * BaseShaderLoader
******************************************************************************/
//シェーダを作成
ShaderProgram *BaseShaderLoader::generateShader(const char *vertexFilename, const char *fragmentFilename)
{
    vertexShaderID = loadShader(vertexFilename, GL_VERTEX_SHADER);
    fragmentShaderID = loadShader(fragmentFilename, GL_FRAGMENT_SHADER);
    programID = glCreateProgram();
    glAttachShader(programID, vertexShaderID);
    glAttachShader(programID, fragmentShaderID);
    bindAttributes();
    glLinkProgram(programID);
    glValidateProgram(programID);
    return new ShaderProgram(programID, vertexShaderID, fragmentShaderID);
}
//シェーダを読み込む
GLuint BaseShaderLoader::loadShader(const char *file, int type)
{
    GLuint ShaderID = glCreateShader(type);

    //読み込み
    if (readShaderSource(ShaderID, file))
    {
        exit(1);
    }
    //コンパイル
    GLint compiled;
    glCompileShader(ShaderID);
    glGetShaderiv(ShaderID, GL_COMPILE_STATUS, &compiled);
    if (compiled == GL_FALSE)
    {
        fprintf(stderr, "Error --> glCompileShader()\n");
    }

    return ShaderID;
}

void BaseShaderLoader::bindAttribute(int attribute, const char *variableName)
{
    glBindAttribLocation(programID, attribute, variableName);
}
/******************************************************************************
 * class StaticShaderLoader
******************************************************************************/
void StaticShaderLoader::bindAttributes()
{
}
/******************************************************************************
 * ShaderProgram
******************************************************************************/
ShaderProgram::ShaderProgram()
{
    this->programID = 0;
    this->vertexShaderID = 0;
    this->fragmentShaderID = 0;
}
ShaderProgram::ShaderProgram(GLuint programID, GLuint vertexShaderID, GLuint fragmentShaderID)
{
    this->programID = programID;
    this->vertexShaderID = vertexShaderID;
    this->fragmentShaderID = fragmentShaderID;
}
void ShaderProgram::startShader()
{
    glUseProgram(programID);
}
void ShaderProgram::stopShader()
{
    glUseProgram(0);
}
