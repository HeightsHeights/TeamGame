#include "testXLoader.h"
#include <string.h>
#include <limits>

#define BUFFER_LENGTH 255

void TestXLoader::skipLine()
{
    skip2Key('\n');
}
void TestXLoader::skip2Key(const char key)
{
    file.ignore(std::numeric_limits<std::streamsize>::max(), file.widen(key));
}
void TestXLoader::readMesh(TestXNode *node)
{
    char key[BUFFER_LENGTH] = {0};
    while (1)
    {
        file >> key;
        if (!(file))
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
void TestXLoader::readFrame(TestXNode *node)
{
    unsigned int currentHierarchy = hierarchy;
    char key[BUFFER_LENGTH] = {0};
    unsigned int begin = 0, end = 0;

    while (1)
    {
        file >> key;
        if (!(file))
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
        else if (strcmp(key, "{") == 0)
        {
            hierarchy++;
        }
        else if (strcmp(key, "}") == 0)
        {
            hierarchy--;
            if (hierarchy == currentHierarchy - 1)
            {
                return;
            }
        }
        else if (0 == strcmp(key, "Frame"))
        {
            std::string frameName;
            file >> frameName;
            unsigned int posFile = file.tellg();
            node->node = new TestXNode();
            node->node->frameName = frameName;
            for (int i = 0; i < hierarchy; i++)
            {
                printf("\t");
            }
            printf("Frame:%s\n", frameName.c_str());
            //readMesh(node->node);
            file.seekg(posFile, std::ios_base::beg);
            readFrame(node->node);
        }
    }
}

void TestXLoader::readXFile()
{
    hierarchy = 0;
    ret->root.frameName = "root";

    //保留
    readFrame(&ret->root);
}

bool TestXLoader::loadXFile(const char *filePath)
{

    file.open(filePath, std::fstream::in);
    if (!file.is_open())
    {
        fprintf(stderr, "Error --> xFile is not found\n");
        return false;
    }

    readXFile();

    file.close();
    return true;
}

TestXModel *TestXLoader::load(const std::string dirPath, const std::string fileName)
{
    std::string xFilePath = dirPath + fileName + ".x";

    ret = new TestXModel();

    if (!loadXFile(xFilePath.c_str()))
    {
        return NULL;
    }

    return ret;
}
