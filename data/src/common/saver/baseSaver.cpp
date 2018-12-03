#include "./baseSaver.h"
#include <limits>

bool BaseSaver::saveFile(const char *filePath)
{
    file.open(filePath, std::ios::in | std::ios::out);
    if (!file.is_open())
    {
        fprintf(stderr, "Error --> file is not found\n");
        return false;
    }

    writeFile();

    file.close();
    return true;
}