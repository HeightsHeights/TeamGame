#include "./configSaver.h"
#include <string>

bool ConfigSaver::writeFile()
{
    file << "Name: " + data->name << std::endl;
    file << "ServerAddress: " + data->serverAddress << std::endl;
    file << "WiiRemoteId: " + data->wiiRemoteId << std::endl;
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