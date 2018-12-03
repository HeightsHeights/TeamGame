#include "./configSaver.h"
#include <string>

bool ConfigSaver::writeFile()
{
    file << "ClientNum: " + data->clientNum;
}

bool ConfigSaver::save(std::string fileName, ConfigData *data)
{
    std::string filePath = "data/res/config/" + fileName + ".dat";

    this->data = data;

    if (!saveFile(filePath.c_str()))
    {
        return false;
    }

    return true;
}