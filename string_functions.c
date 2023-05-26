#include "shell.h"

/**
 * _strcmp - Compares two strings
 * @s1: The first string to be compared.
 * @s2: The second string to be compared.
 *
 * Return: Positive byte difference if s1 > s2
 *         0 if s1 = s2
 *         Negative byte difference if s1 < s2
 */
int _strcmp(char *s1, char *s2)
{
	while (*s1 && *s2 && *s1 == *s2)
	{
		s1++;
		s2++;
	}

	if (*s1 != *s2)
		return (*s1 - *s2);

	return (0);
}

/**
 * _strncmp - Compare two strings.
 * @s1: Pointer to a string.
 * @s2: Pointer to a string.
 * @n: The first n bytes of the strings to compare.
 *
 * Return: Less than 0 if s1 is shorter than s2.
 *         0 if s1 and s2 match.
 *         Greater than 0 if s1 is longer than s2.
 */
int _strncmp(const char *s1, const char *s2, size_t n)
{
    size_t i = 0;

    while (s1[i] && s2[i] && i < n)
    {
        if (s1[i] > s2[i])
            return (s1[i] - s2[i]);
        else if (s1[i] < s2[i])
            return (s1[i] - s2[i]);
        i++;
    }

    if (i == n)
        return 0;
    else
        return -15;
}

/**
 * _strcat - Concantenates two strings
 * @dest: Pointer to destination string
 * @src: Pointer to source string.
 *
 * Return: Pointer to destination string.
 */
char *_strcat(char *dest, const char *src)
{
    char *destTemp;
    const char *srcTemp;

    destTemp = dest;
    srcTemp = src;

    while (*destTemp != '\0')
    {
        destTemp++;
    }

    while (*srcTemp != '\0')
    {
        *destTemp++ = *srcTemp++;
    }

    *destTemp = '\0';

    return dest;
}

/**
 * _strncat - Concantenates two strings where n number
 *            of bytes are copied from source.
 * @dest: Pointer to destination string.
 * @src: Pointer to source string.
 * @n: n bytes to copy from src.
 *
 * Return: Pointer to destination string.
 */
char *_strncat(char *dest, const char *src, size_t n) 
{
    size_t dest_len = _strlen(dest);
    size_t i;

    for (i = 0; i < n && src[i] != '\0'; i++) 
	{
        dest[dest_len + i] = src[i];
    }

    dest[dest_len + i] = '\0';

    return dest;
}