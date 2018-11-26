#include "testXLoader.h"

#define BUFFER_LENGTH 256

bool TestXLoader::loadXFile(const char *filePath)
{
    char buf[BUFFER_LENGTH] = {0};

    file.open(filePath, std::fstream::in);
    if (!file.is_open())
    {
        fprintf(stderr, "Error --> xFile is not found\n");
        return false;
    }
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
