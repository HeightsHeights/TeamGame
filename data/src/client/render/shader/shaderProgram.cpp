#define GL_GLEXT_PROTOTYPES 1

#include "./shaderProgram.h"

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
