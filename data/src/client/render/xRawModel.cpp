#include "./xRawModel.h"
#include <string.h>
#include <limits>

#define BUFFER_OFFSET(bytes) ((GLubyte *)NULL + (bytes))
/******************************************************************************
 * XRawModel
******************************************************************************/
XRawModel::XRawModel()
{
    /* nothing */
}
void XRawModel::setVao(GLuint vao)
{
    this->vao = vao;
}
void XRawModel::pushVertexCount(unsigned int vertexCount)
{
    this->vertexCount.push_back(vertexCount);
}
void XRawModel::draw()
{
    unsigned int beginIndex = 0;
    for (unsigned int i = 0; i < vertexCount.size(); i++)
    {

        glBindVertexArray(vao);
        glDrawElements(GL_TRIANGLES, vertexCount[i], GL_UNSIGNED_INT, BUFFER_OFFSET(beginIndex * sizeof(unsigned int)));
        glBindVertexArray(0);

        beginIndex += vertexCount[i];
    }
}
/******************************************************************************
 * XModelLoader
******************************************************************************/
XModelLoader::XModelLoader()
{
    /* nothing */
}

bool XModelLoader::skipLine()
{
    file.ignore(std::numeric_limits<std::streamsize>::max(), file.widen('\n'));
}
bool XModelLoader::loadXFile()
{
    numVertex = numNormal = 0;
    char buf[OBJ_BUFFER_LENGTH] = {0};
    std::string str;
    while (1)
    {
        file >> buf;

        if (!(file))
        {
            break;
        }
        /* Mesh まで飛ぶ　→　数の分メッシュを読み込む　→　数の分面番号を読み込む */
        if (0 == strcmp(buf, "Mesh"))
        {
            skipLine();

            unsigned int numMesh;
            getline(file, str);
            sscanf(str.data(), "%u;,", &numMesh);

            for (unsigned int i = 0; i < numMesh; i++)
            {
                getline(file, str);
                float x, y, z;
                sscanf(str.data(), "%f;%f;%f;", &x, &y, &z);
                vertices.push_back(Vector3f(x, y, z));
            }
            unsigned int numIndex;
            getline(file, str);
            sscanf(str.data(), "%u;,", &numIndex);
            (*ret).pushVertexCount(numIndex * 3);
            for (int i = 0; i < numIndex; i++)
            {
                getline(file, str);
                unsigned int numPolygon, index1, index2, index3;
                sscanf(str.data(), "%u;%u,%u,%u;", &numPolygon, &index1, &index2, &index3);
                indices.push_back(index1 + numVertex);
                indices.push_back(index2 + numVertex);
                indices.push_back(index3 + numVertex);
            }
        }
        /* MeshNormal まで飛ぶ　→　数の分法線を読み込む →　数の分法線番号を読み込む*/
        else if (0 == strcmp(buf, "MeshNormals"))
        {
            skipLine();

            unsigned int numMeshNomals;
            getline(file, str);
            sscanf(str.data(), "%u;,", &numMeshNomals);

            for (unsigned int i = 0; i < numMeshNomals; i++)
            {
                getline(file, str);
                float x, y, z;
                sscanf(str.data(), "%f;%f;%f;", &x, &y, &z);
                normals.push_back(Vector3f(x, y, z));
                //printf("%5f%5f%5f\n", x, y, z);
            }
            unsigned int numNormalIndex;
            getline(file, str);
            sscanf(str.data(), "%u;,", &numNormalIndex);
            for (int i = 0; i < numNormalIndex; i++)
            {
                getline(file, str);
                unsigned int numPolygon, index1, index2, index3;
                sscanf(str.data(), "%u;%u,%u,%u;", &numPolygon, &index3, &index2, &index1);
                normalIndices.push_back(index1 + numNormal);
                normalIndices.push_back(index2 + numNormal);
                normalIndices.push_back(index3 + numNormal);
                //printf("%5u%5u%5u\n", index1, index2, index3);
            }
            numVertex = vertices.size();
            numNormal = normals.size();
        }
    }
    return true;
}

GLuint XModelLoader::createVao()
{
    GLuint vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    return vao;
}
void XModelLoader::storeAttributeData(const int attributeNumber, const GLsizeiptr size, const float *data, GLboolean normalize)
{
    GLuint vertexBufferObject;
    glGenBuffers(1, &vertexBufferObject);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObject);
    glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
    glEnableVertexAttribArray(attributeNumber);
    glVertexAttribPointer(attributeNumber, 3, GL_FLOAT, normalize, 0, (void *)0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}
void XModelLoader::bindIndicesBuffer(const GLsizeiptr size, const unsigned int *indices)
{
    GLuint indexBufferObject;
    glGenBuffers(1, &indexBufferObject);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBufferObject);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, indices, GL_STATIC_DRAW);
}
void XModelLoader::unbindVao()
{
    glBindVertexArray(0);
}

XRawModel *XModelLoader::load(const char *fileName)
{
    ret = new XRawModel();
    file.open(fileName, std::fstream::in);
    if (!file.is_open())
    {
        fprintf(stderr, "Error --> xFile is not found\n");
        return NULL;
    }

    if (!loadXFile())
    {
        fprintf(stderr, "Error --> laodXFile()\n");
        return NULL;
    }
    file.close();

    Vector3f normalArraySum[vertices.size()];
    for (unsigned int i = 0; i < indices.size(); i++)
    {
        normalArraySum[indices[i]] += normals[normalIndices[i]];
    }

    GLuint vao = createVao();
    bindIndicesBuffer(indices.size() * sizeof(unsigned int), &indices[0]);
    storeAttributeData(0, vertices.size() * sizeof(Vector3f), vertices[0], GL_FALSE);
    storeAttributeData(2, vertices.size() * sizeof(Vector3f), normalArraySum[0], GL_TRUE);
    unbindVao();

    (*ret).setVao(vao);

    return ret;
}