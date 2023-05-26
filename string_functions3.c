#include "shell.h"

/**
 * num_len - Counts the digit length of a number.
 * @num: The number to measure.
 *
 * Return: The digit length.
 */
int num_len(int num)
{
	unsigned int num_abs;
	int length = 1;

	if (num < 0)
	{
		length++;
		num_abs = num * -1;
	}
	else
	{
		num_abs = num;
	}

	while (num_abs > 9)
	{
		length++;
		num_abs /= 10;
	}

	return length;
}

/**
 * _itoa - Converts an integer to a string.
 * @num: The integer.
 *
 * Return: The converted string.
 */
char *_itoa(int num)
{
    char *buffer;
    int len = num_len(num);
    unsigned int num1;
    int i;

    buffer = malloc(sizeof(char) * (len + 1));
    if (!buffer)
        return NULL;

    buffer[len] = '\0';

    if (num < 0)
    {
        num1 = num * -1;
        buffer[0] = '-';
    }
    else
    {
        num1 = num;
    }

    for (i = len - 1; i >= 0; i--)
    {
        buffer[i] = (num1 % 10) + '0';
        num1 /= 10;
    }

    return buffer;
}