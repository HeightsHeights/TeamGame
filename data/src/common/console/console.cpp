#include "./console.h"

#include <stdio.h>
#define MAX_LEN_STRING 256
bool Console::input(const char *message, const char *defaultValue, char *str)
{
    bool isInput = false;
    printf("Input %s", message);
    if (defaultValue != NULL)
    {
        printf("\tDefaultValue (%s)", defaultValue);
    }
    printf("\n> ");

    int c;
    while ((c = getchar()) != '\n')
    {
        *str++ = c;
        isInput = true;
    }
    *str = '\0';
    return isInput;
}

bool Console::scanString(const char *message, const char *defaultValue, std::string *str)
{
    char tmp[MAX_LEN_STRING];
    bool isInput = input(message, defaultValue, tmp);
    if (isInput)
    {
        *str = std::string(tmp);
    }
    else
    {
        *str = std::string(defaultValue);
    }
    return isInput;
}
