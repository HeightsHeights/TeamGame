#include "./guiDataBinder.h"

GLuint GuiDataBinder::dataBind(std::vector<unsigned int> vertexIndices, std::vector<Vector3f> vertexPositions, Vector2f vertexUvs[], Vector3f vertexNormals[])
{
        GLuint vao = createVao();
        bindIndicesBuffer(vertexIndices.size() * sizeof(unsigned int), &vertexIndices[0]);
        unsigned int arraySize = vertexPositions.size();
        storeAttributeData(0, 3, arraySize * sizeof(Vector3f), vertexPositions[0]);
        storeAttributeData(1, 2, arraySize * sizeof(Vector2f), vertexUvs[0]);
        storeAttributeData(2, 3, arraySize * sizeof(Vector3f), vertexNormals[0]);
        unbindVao();

        return vao;
}

GLuint GuiDataBinder::createVao()
{
        GLuint vao;
        glGenVertexArrays(1, &vao);
        glBindVertexArray(vao);
        return vao;
}
void GuiDataBinder::storeAttributeData(const int attributeNumber, const int num, const GLsizeiptr size, const float *data)
{
        GLuint vertexBufferObject;
        glGenBuffers(1, &vertexBufferObject);
        glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObject);
        glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
        glEnableVertexAttribArray(attributeNumber);
        glVertexAttribPointer(attributeNumber, num, GL_FLOAT, GL_FALSE, 0, (void *)0);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
}
void GuiDataBinder::bindIndicesBuffer(const GLsizeiptr size, const unsigned int *indices)
{
        GLuint indexBufferObject;
        glGenBuffers(1, &indexBufferObject);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBufferObject);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, indices, GL_STATIC_DRAW);
}
void GuiDataBinder::unbindVao()
{
        glBindVertexArray(0);
}