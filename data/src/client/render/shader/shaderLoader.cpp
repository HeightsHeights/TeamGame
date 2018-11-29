#define GL_GLEXT_PROTOTYPES 1

#include "./shaderLoader.h"
#include <GL/glut.h>
#include "./glsl.h"
#include <stdio.h>

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

void BaseShaderLoader::bindAttributes()
{
}

/******************************************************************************
 * class StaticShaderLoader
******************************************************************************/
void StaticShaderLoader::bindAttributes()
{
    bindAttribute(0, "position");
    //bindAttribute(2, "normal");
}
/******************************************************************************
 * class TestShaderLoader
******************************************************************************/
void TestShaderLoader::bindAttributes()
{
    //bindAttribute(0, "position");
    //bindAttribute(2, "normal");
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