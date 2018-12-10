#include "./baseLoader.h"
#include <limits>

void BaseLoader::skipLine()
{
    skip2Key('\n');
}
void BaseLoader::skip2Key(const char key)
{
    file.ignore(std::numeric_limits<std::streamsize>::max(), file.widen(key));
}
unsigned int BaseLoader::getFilePos()
{
    return file.tellg();
}
void BaseLoader::jumpFile(unsigned int pos)
{
    file.seekg(pos, std::fstream::beg);
}
bool BaseLoader::loadFile(const char *filePath)
{
    file.open(filePath, std::fstream::in);
    if (!file.is_open())
    {
        fprintf(stderr, "Error --> file is not found\n");
        return false;
    }

    readFile();

    file.close();
    return true;
}