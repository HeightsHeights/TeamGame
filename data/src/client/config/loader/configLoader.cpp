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
        if (0 == strcmp(key, "Name:"))
        {
            file >> ret->name;
        }
        else if (0 == strcmp(key, "ServerAddress:"))
        {
            file >> ret->serverAddress;
        }
        else if (0 == strcmp(key, "WiiRemoteId:"))
        {
            file >> ret->wiiRemoteId;
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