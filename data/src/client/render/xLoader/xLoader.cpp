#include "xLoader.h"
#include <string.h>
#include <limits>

#define FILE_EXTENSION ".x"

void XLoader::readMesh(XNode *node)
{
    char key[BUFFER_LENGTH] = {0};
    while (1)
    {
        file >> key;
        if (!file)
        {
            break;
        }
        if (0 == strcmp(key, "Mesh"))
        {
            skipLine();

            std::string lineString;

            unsigned int numMesh;
            getline(file, lineString);
            sscanf(lineString.data(), "%u;,", &numMesh);

            for (unsigned int i = 0; i < numMesh; i++)
            {
                getline(file, lineString);
                float x, y, z;
                sscanf(lineString.data(), "%f;%f;%f;", &x, &y, &z);
                vertices.push_back(Vector3f(x, y, z));
            }
            return;
            unsigned int numIndex;
            getline(file, lineString);
            sscanf(lineString.data(), "%u;,", &numIndex);

            for (int i = 0; i < numIndex; i++)
            {
                getline(file, lineString);
                unsigned int numPolygon, index1, index2, index3;
                sscanf(lineString.data(), "%u;%u,%u,%u;", &numPolygon, &index1, &index2, &index3);
                vertexIndices.push_back(index1);
                vertexIndices.push_back(index2);
                vertexIndices.push_back(index3);
            }
        }
        else if (0 == strcmp(key, "MeshNormals"))
        {
            skipLine();

            std::string lineString;

            unsigned int numMeshNomals;
            getline(file, lineString);
            sscanf(lineString.data(), "%u;,", &numMeshNomals);

            for (unsigned int i = 0; i < numMeshNomals; i++)
            {
                getline(file, lineString);
                float x, y, z;
                sscanf(lineString.data(), "%f;%f;%f;", &x, &y, &z);
                normals.push_back(Vector3f(x, y, z));
            }
            unsigned int numNormalIndex;
            getline(file, lineString);
            sscanf(lineString.data(), "%u;,", &numNormalIndex);
            for (int i = 0; i < numNormalIndex; i++)
            {
                getline(file, lineString);
                unsigned int numPolygon, index1, index2, index3;
                sscanf(lineString.data(), "%u;%u,%u,%u;", &numPolygon, &index3, &index2, &index1);
                normalIndices.push_back(index1);
                normalIndices.push_back(index2);
                normalIndices.push_back(index3);
            }
        }
    }
    return;
}
void XLoader::readFrame(XNode *node, int hierarchy)
{
    int currentHierarchy = hierarchy;
    char key[BUFFER_LENGTH] = {0};
    int begin = 0, end = 0;

    while (1)
    {
        file >> key;
        if (!file)
        {
            break;
        }
        if (0 == strcmp(key, "Header"))
        {
            skip2Key('}');
        }
        else if (0 == strcmp(key, "template"))
        {
            skip2Key('}');
        }
        else if (0 == strcmp(key, "{"))
        {
            begin++;
        }
        else if (0 == strcmp(key, "}"))
        {
            end++;
        }
        else if (0 == strcmp(key, "Frame"))
        {
            std::string frameName;
            file >> frameName;

            if (begin > end || ((begin == 0) && (end == 0)))
            {
                node->node = new XNode(frameName);
                unsigned int posFile = file.tellg();
                readMesh(node->node);
                file.seekg(posFile, std::fstream::beg);
                readFrame(node->node, currentHierarchy + 1);
            }
            if (back == currentHierarchy)
            {
                back = -1;
                node->next = new XNode(std::string(buffer));
                unsigned int posFile = file.tellg();
                readMesh(node->next);
                file.seekg(posFile, std::fstream::beg);
                readFrame(node->next, currentHierarchy);
            }
            if (begin < end) // too many "}"
            {
                strcpy(buffer, frameName.c_str());
                back = currentHierarchy - (end - begin);
                return;
            }
            if (begin == end && begin != 0 && end != 0)
            {
                node->next = new XNode(frameName);
                unsigned int posFile = file.tellg();
                readMesh(node->next);
                file.seekg(posFile, std::fstream::beg);
                readFrame(node->next, currentHierarchy);
            }
            if ((back != -1) && (back < currentHierarchy))
            {
                return;
            }
        }
    }
}

bool XLoader::readFile()
{
    int rootHierarchy = 0;
    ret->root.frameName = "root";
    back = -1;
    //保留
    readFrame(&ret->root, rootHierarchy);
}

XModel *XLoader::load(const std::string dirPath, const std::string fileName)
{
    std::string xFilePath = dirPath + fileName + FILE_EXTENSION;

    ret = new XModel();

    if (!loadFile(xFilePath.c_str()))
    {
        return NULL;
    }

    return ret;
}
