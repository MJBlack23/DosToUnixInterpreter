#include <string.h>
#include <ctype.h>

int string_len(char *str)
{
    int len = 0;
    while (str[len] != '\0')
    {
        ++len;
    }

    return len;
}

char *string_reverse(char *str)
{
    int len = string_len(str);
    int i, end = len - 1;
    char temp[len];
    char *new_str;

    for (i = 0; i < len; ++i)
    {
        temp[i] = str[end];
        --end;
    }

    // create a proper string with a null termination
    temp[i] = '\0';

    strcpy(new_str, temp);
    return new_str;
}

char *left_trim(char *str)
{
    while (isspace((unsigned char)*str))
    {
        str++;
    }

    // strcpy(trimmed, str);

    return str;
}

char *right_trim(char *str)
{
    char *reversed = string_reverse(str);

    char *right_trimmed = left_trim(reversed);

    return string_reverse(right_trimmed);
}