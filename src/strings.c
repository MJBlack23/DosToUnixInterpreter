#include <string.h>
#include <ctype.h>

int word_count(char str[])
{
    int iter = 0;
    int spaces = 1;
    while (str[iter] != '\0')
    {
        if (str[iter] == ' ')
            spaces++;

        ++iter;
    }

    return spaces;
}

int left_trim(char str[])
{
    int n;

    for (n = 0; n <= strlen(str) - 1; n++)
    {
        if (!isspace(str[n]))
            break;
    }
    return strlen(str) - n;
}

int right_trim(char str[])
{
    int n;

    for (n = strlen(str) - 1; n >= 0; n--)
    {
        if (!isspace(str[n]))
            break;
    }

    str[n + 1] = '\0';
    return n;
}