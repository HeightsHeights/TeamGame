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
    GLint linked;
    glLinkProgram(programID);
    glGetProgramiv(programID, GL_LINK_STATUS, &linked);
    printProgramInfoLog(programID);
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
    printShaderInfoLog(ShaderID);
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
GLint BaseShaderLoader::getAttribute(const char *variableName)
{
    return glGetAttribLocation(programID, variableName);
}
GLint BaseShaderLoader::getUniform(const char *variableName)
{
    return glGetUniformLocation(programID, variableName);
}
void BaseShaderLoader::bindAttributes()
{
}

/******************************************************************************
 * class StaticShaderLoader
******************************************************************************/
void StaticShaderLoader::bindAttributes()
{
    //bindAttribute(0, "position");
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
void GuiShaderLoader::bindAttributes()
{
    // // 何番目のattribute変数か
    // int positionLocation = getAttribute("position");
    // int uvLocation = getAttribute("uv");
    // int textureLocation = getUniform("texture");

    // // attribute属性を有効にする
    // glEnableVertexAttribArray(positionLocation);
    // glEnableVertexAttribArray(uvLocation);

    // // uniform属性を設定する
    // glUniform1i(textureLocation, 0);
}
