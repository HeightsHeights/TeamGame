#include "./configLoader.h"
#include <string.h>

#define DIR_PATH "data/res/config/"
#define FILE_EXTENSION ".dat"
#define BUFFER_LENGTH 256

bool ConfigLoader::readFile()
{
    char key[BUFFER_LENGTH] = {0};
    while (1)
    {
        file >> key;
        if (!file)
        {
            break;
        }
        if (0 == strcmp(key, "ClientNum:"))
        {
            file >> ret->clientNum;
        }
    }
}

ConfigData *ConfigLoader::load(std::string fileName)
{
    std::string filePath = DIR_PATH + fileName + FILE_EXTENSION;

    ret = new ConfigData();

    if (!loadFile(filePath.c_str()))
    {
        return NULL;
    }

    return ret;
}