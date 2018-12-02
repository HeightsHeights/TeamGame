#include "./console.h"

#include <stdio.h>
void Console::inputString(char *message, char *str)
{
    printf("input %s\n", message);
    printf("> ");
    scanf("%s", str);
}