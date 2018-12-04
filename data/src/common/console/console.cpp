#include "./console.h"

#include <stdio.h>
#define MAX_LEN_STRING 256
bool Console::input(char *str)
{
    bool isInput = false;

    printf("> ");

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
    printf("Input %s", message);
    if (defaultValue != NULL)
    {
        printf("\t(DefaultValue --> \"%s\")", defaultValue);
    }
    printf("\n");

    char tmp[MAX_LEN_STRING];
    bool isInput = input(tmp);
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
