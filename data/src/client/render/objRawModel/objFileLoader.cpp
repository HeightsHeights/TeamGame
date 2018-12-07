#include "./objFileLoader.h"
#include "./objDataBinder.h"
#include <string.h>

#define OBJ_BUFFER_LENGTH 256

bool ObjFileLoader::readFile()
{
    char buf[OBJ_BUFFER_LENGTH] = {0};
    while (1)
    {
        file >> buf;
        if (!file)
        {
            break;
        }
        if (0 == strcmp(buf, "o"))
        {
            createSubset();
        }
        else if (0 == strcmp(buf, "usemtl"))
        {
            file.seekg(-6, std::ios_base::cur);
            createSubset();
        }
    }
    return true;
}

void ObjFileLoader::createSubset()
{
    char buf[OBJ_BUFFER_LENGTH] = {0};

    unsigned int numVertex = 0;

    int materialId;

    while (1)
    {
        file >> buf;
        if (!(file))
        {
            break;
        }
        if (0 == strcmp(buf, "v"))
        {
            float x, y, z;
            file >> x >> y >> z;
            vertices.push_back(Vector3f(x, y, z));
        }
        else if (0 == strcmp(buf, "vt"))
        {
            float u, v;
            file >> u >> v;
            textures.push_back(Vector2f(u, 1.0f - v));
        }
        else if (0 == strcmp(buf, "vn"))
        {
            float x, y, z;
            file >> x >> y >> z;
            normals.push_back(Vector3f(x, y, z));
        }
        else if (0 == strcmp(buf, "usemtl"))
        {
            file >> buf;
            materialId = model->getMtlId(buf);
            break;
        }
    }
    while (1)
    {
        file >> buf;
        if (!file)
        {
            break;
        }

        if (0 == strcmp(buf, "o"))
        {
            file.seekg(-1, std::ios_base::cur);
            break;
        }
        else if (0 == strcmp(buf, "usemtl"))
        {
            file.seekg(-6, std::ios_base::cur);
            break;
        }
        else if (0 == strcmp(buf, "f"))
        {
            unsigned int iVertex, iTexCoord, iNormal;
            for (int iFace = 0; iFace < 3; iFace++)
            {
                numVertex++;
                file >> iVertex;
                vertexIndices.push_back(iVertex - 1);

                if ('/' == file.peek())
                {
                    file.ignore();

                    if ('/' != file.peek())
                    {
                        file >> iTexCoord;
                        textureIndices.push_back(iTexCoord - 1);
                    }

                    if ('/' == file.peek())
                    {
                        file.ignore();
                        file >> iNormal;
                        normalIndices.push_back(iNormal - 1);
                    }
                }
                //改行
                if ('\n' == file.peek())
                {
                    break;
                }
            }
        }
    }

    model->pushSubset(ObjSubset(numVertex, materialId));
}

void ObjFileLoader::processVertex(unsigned int textureIndexArray[], Vector2f uvArray[], Vector3f normalSumArray[])
{
    for (unsigned int i = 0; i < vertices.size(); i++)
    {
        textureIndexArray[i] = 0;
    }

    for (unsigned int i = 0; i < vertexIndices.size(); i++)
    {
        if (textureIndexArray[vertexIndices[i]] == 0)
        {
            textureIndexArray[vertexIndices[i]] = textureIndices[i];
        }
        else if (textureIndexArray[vertexIndices[i]] != textureIndices[i])
        {
            vertices.push_back(vertices[vertexIndices[i]]);
            vertexIndices[i] = vertices.size() - 1;
        }
    }
    for (unsigned int i = 0; i < vertexIndices.size(); i++)
    {
        uvArray[vertexIndices[i]] = textures[textureIndices[i]];
    }

    for (unsigned int i = 0; i < vertexIndices.size(); i++)
    {
        normalSumArray[vertexIndices[i]] += normals[normalIndices[i]];
    }
}

bool ObjFileLoader::load(const char *filePath)
{
    if (!loadFile(filePath))
    {
        return false;
    }

    unsigned int textureIndexArray[vertices.size()];
    Vector2f uvArray[vertexIndices.size()];
    Vector3f normalSumArray[vertexIndices.size()];

    processVertex(textureIndexArray, uvArray, normalSumArray);
    GLuint vao = ObjDataBinder().dataBind(vertexIndices, vertices, uvArray, normalSumArray);
    model->setVao(vao);

    return true;
}