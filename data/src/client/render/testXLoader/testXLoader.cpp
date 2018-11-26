#include "testXLoader.h"
#include <string.h>
#include <limits>

#define BUFFER_LENGTH 256

void TestXLoader::skipLine()
{
    skip2Key('\n');
}
void TestXLoader::skip2Key(const char key)
{
    file.ignore(std::numeric_limits<std::streamsize>::max(), file.widen(key));
}
void TestXLoader::readMesh()
{
}
void TestXLoader::readFrame(TestXNode *node)
{
    char key[BUFFER_LENGTH] = {0};

    file >> key;

    while (1)
    {
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
        else if (0 == strcmp(key, "Frame"))
        {
            std::string frameName;
            file >> frameName;
            node->node = new TestXNode();
            node->node->frameName = frameName;
        }
    }
}

void TestXLoader::readXFile()
{
    ret->root.node = NULL;
    ret->root.next = NULL;
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
