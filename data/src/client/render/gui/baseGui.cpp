#include "./baseGui.h"

BaseGui::BaseGui()
{
}
BaseGui::BaseGui(GLuint texId)
{
    this->texId = texId;

    const GLfloat vertexData[] = {
        -1.0f, -1.0f, 0.0f,
        1.0f, -1.0f, 0.0f,
        -1.0f, 1.0f, 0.0f,
        1.0f, 1.0f, 0.0f};
    const GLuint indexData[] = {
        0, 1, 2,
        2, 1, 3};
    const GLfloat uvData[] = {
        0.0f, 1.0f,
        1.0f, 1.0f,
        0.0f, 0.0f,
        1.0f, 0.0f};
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    GLuint vertexBufferObject;
    GLuint uvBufferObject;
    GLuint indexBufferObject;
    glGenBuffers(1, &indexBufferObject);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBufferObject);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indexData), indexData, GL_DYNAMIC_DRAW);
    glGenBuffers(1, &vertexBufferObject);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObject);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData), vertexData, GL_DYNAMIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void *)0);
    glGenBuffers(1, &uvBufferObject);
    glBindBuffer(GL_ARRAY_BUFFER, uvBufferObject);
    glBufferData(GL_ARRAY_BUFFER, sizeof(uvData), uvData, GL_DYNAMIC_DRAW);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (void *)0);
    glBindVertexArray(0);
}
void BaseGui::draw()
{
    glBindTexture(GL_TEXTURE_2D, texId);
    glBindVertexArray(vao);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (void *)0);
    glBindVertexArray(0);
    glBindTexture(GL_TEXTURE_2D, 0);
}
void BaseGui::draw(GuiRect *srcRect, GuiRect *dstRect)
{
}