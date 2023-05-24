#include <stdio.h>
#include "shell.h"

int _strncmp(const char *s1, const char *s2, int n)
{
    int i;
    
    for (i = 0; i < n && s1[i] && s2[i] && s1[i] == s2[i]; i++);
    
    if (i == n)
        return 0;
    else
        return s1[i] - s2[i];
}

int _strlen(const char *s)
{
    int length = 0;
    
    while (*s++)
        length++;
    
    return length;
}

char *_strcpy(char *dest, const char *src)
{
    char *dest_start = dest;
    
    while (*src)
        *dest++ = *src++;
        
    *dest = '\0';
    
    return dest_start;
}

int _strcmp(const char *s1, const char *s2)
{
    while (*s1 && *s2 && *s1 == *s2) {
        s1++;
        s2++;
    }
    
    return *s1 - *s2;
}

char *_strcat(char *dest, const char *src)
{
    char *dest_start = dest;
    
    while (*dest)
        dest++;
    
    while (*src)
        *dest++ = *src++;
        
    *dest = '\0';
    
    return dest_start;
}
