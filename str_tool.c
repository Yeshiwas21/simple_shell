#include <stdio.h>
#include "shell.h"
/**
* _strncmp - compares two strings up to n bytes
* @s1: compared to s2
* @s2: compared to s1
* @n: number of bytes
*
* Return: difference between s1 and s2
*/
int _strncmp(char *s1, char *s2, int n)
{
	int i;

	for (i = 0; s1[i] && s2[i] && i < n; i++)
	{
		if (s1[i] != s2[i])
			return (s1[i] - s2[i]);
	}
	return (0);
}
/**
 * _strlen -  returns the length of a string
 * @s:string
 * Return: length
 */
int _strlen(char *s)
{
	int longi = 0;

	while (*s != '\0')
	{
		longi++;
		s++;
	}
	return (longi);
}
/**
 * *_strcpy - copies the string pointed by src,
 * including the terminating null byte (\0),
 * to the buffer pointed to by dest
 * @dest: pointer  in buffer to be copied
 * @src: string to be copied
 * Return: pointer to dest
 */
char *_strcpy(char *dest, char *src)
{
	int len, i;

	len = 0;

	while (src[len] != '\0')
	{
		len++;
	}
	for (i = 0; i < len; i++)
	{
		dest[i] = src[i];
	}
	dest[i] = '\0';
	return (dest);
}
/**
 * _strcmp - compares two strings
 * @s1: pointer to first string
 * @s2: pointer to second string
 * Return: if str1 < str2, negative difference is unmatched char
 * if str1 == str2, 0
 * if str1 > str2, positive difference is unmatched char
 */
int _strcmp(char *s1, char *s2)
{
	while (*s1 && *s2 && *s1 == *s2)
	{
		s1++;
		s2++;
	}
	return (*s1 - *s2);
}
/**
 *  *_strcat- concatinate two strings
 *  @dest: first string
 *  @src: second string
 *  Return: pointer
 */
char  *_strcat(char *dest, char *src)
{
	int r = 0;

	int s = 0;

	while (dest[r] != '\0')
	{
		r++;
	}
	while (src[s] != '\0')
	{
		dest[r] = src[s];
		r++;
		s++;
	}
	dest[r] = '\0';
	return (dest);
}
