#include "./particle.h"

#define BUFFER_OFFSET(bytes) ((GLubyte *)NULL + (bytes))

Particle::Particle() {}
Particle::Particle(GLuint texId)
{
    this->texId = texId;
}
void Particle::setSpriteNum(Touple2f spriteMaxNum)
{
    this->spriteMaxNum = spriteMaxNum;
}

void Particle::bindVao()
{
    glBindVertexArray(vao);
}
void Particle::unbindVao()
{
    glBindVertexArray(0);
}

void Particle::bindTexture()
{
    glBindTexture(GL_TEXTURE_2D, texId);
}
void Particle::unbindTexture()
{
    glBindTexture(GL_TEXTURE_2D, 0);
}

GLuint Particle::createArrayBuffer()
{
    GLuint vbo;
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vboVertex);
    return vbo;
}
void Particle::storeData()
{
    std::function<int(int, int)> plus = [](int a, int b) { return a + b; };
    plus(1, 1);

    const GLuint indexData[] = {
        0, 2, 3,
        0, 3, 1};
    const GLfloat vertexData[] = {
        -1.0f, 1.0f, 0.0f,
        1.0f, 1.0f, 0.0f,
        -1.0f, -1.0f, 0.0f,
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

    vboVertex = createArrayBuffer();
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData), vertexData, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void *)0);

    vboUv = createArrayBuffer();
    glBufferData(GL_ARRAY_BUFFER, sizeof(uvData), uvData, GL_DYNAMIC_DRAW);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (void *)0);

    vboPos = createArrayBuffer();
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(pData), (void *)0);

    glVertexAttribDivisor(0, 0);
    glVertexAttribDivisor(1, 0);
    glVertexAttribDivisor(2, 1);
    unbindVao();
}

void Particle::generate(unsigned int num)
{
    for (int i = 0; i < num; i++)
    {
        PData object = PData();
        object.pos = this->emitterPos;
        pData.push_back(object);
    }
}
void Particle::draw()
{
    bindVao();

    // glBindBuffer(GL_ARRAY_BUFFER, posBufferObject);
    // glBufferSubData(GL_ARRAY_BUFFER, 0, R * 3 * sizeof(GLfloat), position_data);
    // glBindBuffer(GL_ARRAY_BUFFER, colorbuffer);
    // glBufferSubData(GL_ARRAY_BUFFER, 0, R * 3 * sizeof(GLfloat), g_color_buffer_data);
    glDrawElementsInstanced(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (void *)0, pData.size());
    unbindVao();
}
void Particle::update()
{
    for (int i = 0; i < pData.size(); i++)
    {
    }
}