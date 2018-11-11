#include "../../header/render/xRawModel.h"
#include <string.h>
#include <limits>
/******************************************************************************
 * XRawModel
******************************************************************************/
XRawModel::XRawModel()
{
    /* nothing */
}
void XRawModel::draw()
{
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

    char buf[OBJ_BUFFER_LENGTH] = {0};
    std::string str;
    while (1)
    {
        /* Mesh まで飛ぶ　→　数の分メッシュを読み込む　→　数の分面番号を読み込む */
        file >> buf;

        if (!(file))
        {
            break;
        }
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
                sscanf(str.data(), "%f;%f;%f;,", &x, &y, &z);
                printf("%f%f%f\n", x, y, z);
            }
        }

        /* MeshNormal まで飛ぶ　→　数の分法線を読み込む →　数の分法線番号を読み込む*/
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

    return ret;
}