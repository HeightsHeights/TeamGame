#include "../../header/shader.h"
#include "../../header/glsl.h"
#include <stdio.h>

const char *VERTEX_FILE = "../../shader/staticVertexShader.vert";
const char *FRAGMENT_FILE = "../../shader/staticFragmentShader.frag";

ShaderProgram ShaderManager::shaders;

/******************************************************************************
 * コンストラクタ
******************************************************************************/

/******************************************************************************
 * ShaderManager
******************************************************************************/
bool ShaderManager::initShader()
{
    shaders = StaticShaderLoader().generateShader(VERTEX_FILE, FRAGMENT_FILE);
    return true;
}

void ShaderManager::startShader()
{
    shaders.startShader();
}

void ShaderManager::stopShader()
{
    shaders.stopShader();
}
/******************************************************************************
 * BaseShaderLoader
******************************************************************************/
ShaderProgram BaseShaderLoader::generateShader(const char *vertexFilename, const char *fragmentFilename)
{
    vertexShaderID = loadShader(vertexFilename, GL_VERTEX_SHADER);
    fragmentShaderID = loadShader(fragmentFilename, GL_FRAGMENT_SHADER);
    programID = glCreateProgram();
    glAttachShader(programID, vertexShaderID);
    glAttachShader(programID, fragmentShaderID);
    bindAttributes();
    glLinkProgram(programID);
    glValidateProgram(programID);
    return *new ShaderProgram(programID, vertexShaderID, fragmentShaderID);
}

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
        printf("error compile shader\n");
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