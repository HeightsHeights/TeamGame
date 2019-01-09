#include "./baseGui.h"

#include "../render/shader/shaderManager.h"

#define WINDOW_WIDTH 1280
#define WINDOW_HEIGHT 720
BaseGui::BaseGui()
{
}
BaseGui::BaseGui(GLuint texId)
{
    this->texId = texId;
    storeData();
}
BaseGui::BaseGui(GLuint texId, Vector2f textureSize)
{
    this->texId = texId;
    this->textureSize = textureSize;
    storeData();
}
BaseGui::~BaseGui()
{
    glDeleteTextures(1, &texId);
    glDeleteBuffers(1, &vboIndex);
    glDeleteBuffers(1, &vboVertex);
    glDeleteBuffers(1, &vboUv);
    glDeleteVertexArrays(1, &vao);
}
void BaseGui::draw()
{
    bindTexture();
    bindVao();
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (void *)0);
    unbindVao();
    unbindTexture();
}
void BaseGui::draw(GuiRect *srcRect, GuiRect *dstRect)
{
    draw(srcRect, dstRect, 1.0f);
}
void BaseGui::draw(GuiRect *srcRect, GuiRect *dstRect, float brightness)
{
    if (brightness < 0)
    {
        brightness = 0.0;
    }
    if (brightness > 1)
    {
        brightness = 1.0f;
    }
    GLint loc = glGetUniformLocation(ShaderManager::getProgramId(SID_GUI), "brightness");
    glUniform1f(loc, brightness);

    bindTexture();
    bindVao();

    if (srcRect == NULL)
    {
        srcRect = new GuiRect(0, 0, textureSize.x, textureSize.y);
    }

    if (dstRect == NULL)
    {
        dstRect = new GuiRect(-WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2, WINDOW_WIDTH, WINDOW_HEIGHT);
    }

    const GLfloat vertexData[] = {
        dstRect->pos.x, dstRect->pos.y, 0.0f,
        dstRect->pos.x + dstRect->size.x, dstRect->pos.y, 0.0f,
        dstRect->pos.x, dstRect->pos.y - dstRect->size.y, 0.0f,
        dstRect->pos.x + dstRect->size.x, dstRect->pos.y - dstRect->size.y, 0.0f};

    const GLfloat uvData[] = {
        srcRect->pos.x / textureSize.x, srcRect->pos.y / textureSize.y,
        (srcRect->pos.x + srcRect->size.x) / textureSize.x, srcRect->pos.y / textureSize.y,
        srcRect->pos.x / textureSize.x, (srcRect->pos.y + srcRect->size.y) / textureSize.y,
        (srcRect->pos.x + srcRect->size.x) / textureSize.x, (srcRect->pos.y + srcRect->size.y) / textureSize.y};

    glBindBuffer(GL_ARRAY_BUFFER, vboVertex);
    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertexData), vertexData);
    glBindBuffer(GL_ARRAY_BUFFER, vboUv);
    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(uvData), uvData);

    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (void *)0);
    unbindVao();
    unbindTexture();
}
Vector2f BaseGui::getTextureSize()
{
    return this->textureSize;
}
void BaseGui::bindVao()
{
    glBindVertexArray(vao);
}
void BaseGui::unbindVao()
{
    glBindVertexArray(0);
}

void BaseGui::bindTexture()
{
    glBindTexture(GL_TEXTURE_2D, texId);
}
void BaseGui::unbindTexture()
{
    glBindTexture(GL_TEXTURE_2D, 0);
}
void BaseGui::storeData()
{
    const GLuint indexData[] = {
        0, 2, 3,
        0, 3, 1};
    const GLfloat vertexData[] = {
        0.0f, 0.0f, 0.0f,
        1.0f, 0.0f, 0.0f,
        0.0f, -1.0f, 0.0f,
        1.0f, -1.0f, 0.0f};
    const GLfloat uvData[] = {
        0.0f, 0.0f,
        1.0f, 0.0f,
        0.0f, 1.0f,
        1.0f, 1.0f};

    glGenVertexArrays(1, &vao);
    bindVao();
    glGenBuffers(1, &vboIndex);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vboIndex);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indexData), indexData, GL_STATIC_DRAW);

    glGenBuffers(1, &vboVertex);
    glBindBuffer(GL_ARRAY_BUFFER, vboVertex);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData), vertexData, GL_DYNAMIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void *)0);

    glGenBuffers(1, &vboUv);
    glBindBuffer(GL_ARRAY_BUFFER, vboUv);
    glBufferData(GL_ARRAY_BUFFER, sizeof(uvData), uvData, GL_DYNAMIC_DRAW);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (void *)0);

    unbindVao();
}