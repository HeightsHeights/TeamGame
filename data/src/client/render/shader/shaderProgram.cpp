#define GL_GLEXT_PROTOTYPES 1

#include "./shaderProgram.h"

void ShaderProgram::startShader()
{
    glUseProgram(programID);
}
void ShaderProgram::stopShader()
{
    glUseProgram(0);
}
