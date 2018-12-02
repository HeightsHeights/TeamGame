#include "./baseSaver.h"
#include <limits>

bool BaseSaver::saveFile(const char *filePath)
{
    file.open(filePath, std::ios::in | std::ios::out);
    if (!file.is_open())
    {
        fprintf(stderr, "Error --> file is not found\n");
        file = std::ofstream(filePath);
    }

    writeFile();

    file.close();
    return true;
}