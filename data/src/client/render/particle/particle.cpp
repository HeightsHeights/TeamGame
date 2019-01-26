#include "./particle.h"
#include "../shader/shaderManager.h"
#include <algorithm>
#define BUFFER_OFFSET(bytes) ((GLubyte *)NULL + (bytes))
Particle::Particle() {}
Particle::Particle(GLuint texId, unsigned int maxnum)
{
    this->texId = texId;
    storeData(maxnum);
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
void Particle::storeData(unsigned int maxnum)
{
    // std::function<int(int, int)> plus = [](int a, int b) { return a + b; };
    // plus(1, 1);

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

    GLfloat posData[maxnum * 3];

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
    // vboPos = createArrayBuffer();
    glGenBuffers(1, &vboPos);
    glBindBuffer(GL_ARRAY_BUFFER, vboPos);
    glBufferData(GL_ARRAY_BUFFER, maxnum * 3 * sizeof(GLfloat), NULL, GL_DYNAMIC_DRAW);
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, (void *)0);

    // glVertexAttribDivisor(2, 1);
    // vboPos = createArrayBuffer();
    // glEnableVertexAttribArray(2);
    // glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(pData), (void *)0);

    glVertexAttribDivisor(0, 0);
    glVertexAttribDivisor(1, 0);
    glVertexAttribDivisor(2, 1);

    unbindVao();
}

void Particle::generate(unsigned int num)
{
    this->emitterPos = Vector3f(0.0f, 1.0f, 0.0f);

    for (int i = 0; i < num; i++)
    {
        PData object = PData();
        object.transform.position = this->emitterPos;
        object.life = 1000;

        object.speed = Vector3f((float)(rand() % 501 - 250) / 500, (float)(rand() % 501) / 200, (float)(rand() % 501 - 250) / 500);
        pData.push_back(object);
    }
}
int Particle::draw(float brightness)
{
    if (pData.size() < 1)
    {
        pData.shrink_to_fit();
        return 0;
    }
    if (pData.size() > 20)
        int a = 11;
    GLfloat posData[pData.size() * 3];
    for (int i = 0; i < pData.size(); i++)
    {
        posData[3 * i] = pData[i].transform.position.x;
        posData[3 * i + 1] = pData[i].transform.position.y;
        posData[3 * i + 2] = pData[i].transform.position.z;
    }

    if (brightness < 0)
    {
        brightness = 0.0;
    }
    if (brightness > 1)
    {
        brightness = 1.0f;
    }
    GLint loc = glGetUniformLocation(ShaderManager::getProgramId(SID_PARTICLE), "brightness");
    glUniform1f(loc, brightness);

    bindTexture();
    bindVao();
    glBindBuffer(GL_ARRAY_BUFFER, vboPos);
    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(posData), posData);
    // glBindBuffer(GL_ARRAY_BUFFER, colorbuffer);
    // glBufferSubData(GL_ARRAY_BUFFER, 0, R * 3 * sizeof(GLfloat), g_color_buffer_data);
    glDrawElementsInstanced(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (void *)0, pData.size());
    unbindVao();
    unbindTexture();
    update();
    return 1;
}

#include <iostream>
void Particle::update()
{

    for (int i = 0; i < pData.size(); i++)
    {
        pData[i].life -= 10;
        if (pData[i].life > 0 && pData[i].transform.position.y >= 0)
        {
            pData[i].accel = Vector3f(0.0f, 0.0098f, 0.0f);
            pData[i].speed -= pData[i].accel;
            pData[i].transform.position += pData[i].speed;
        }
        else
        {
            std::iter_swap(pData.begin() + i, pData.end());
            pData.pop_back();
            // if (pData.size() > 0)
            //
        }
    }
}