#include "shell.h"

/**
 * token_length - Locates the delimiter index marking the end
 *             of the first token contained within a string.
 * @string: The string to be searched.
 * @delim_char: The delimiter character.
 *
 * Return: The delimiter index
 */
int token_length(char *string, char *delim_char)
{
	int index = 0, string_len = 0;

	while (*(string + index) && *(string + index) != *delim_char)
	{
		string_len++;
		index++;
	}

	return (string_len);
}

/**
 * count_tokens - Counts the number of delimited
 *                words contained within a string.
 * @str: The string to be searched.
 * @delim: The delimiter character.
 *
 * Return: The number of words contained within str.
 */
int count_tokens(char *str, char *delim)
{
	int index, tokens = 0, len = 0;

	for (index = 0; *(str + index); index++)
		len++;

	for (index = 0; index < len; index++)
	{
		if (*(str + index) != *delim)
		{
			tokens++;
			index += token_length(str + index, delim);
		}
	}

	return (tokens);
}

/**
 * token_strtok - Tokenizes a string.
 * @string: The string.
 * @delim_char: The delimiter character to tokenize the string by.
 *
 * Return: A pointer to an array containing the tokenized words.
 */
char **token_strtok(char *string, char *delim_char)
{
	char **ptr;
	int index = 0, tokens, t, letters, l;

	tokens = count_tokens(string, delim_char);
	if (tokens == 0)
		return (NULL);

	ptr = malloc(sizeof(char *) * (tokens + 2));
	if (!ptr)
		return (NULL);

	for (t = 0; t < tokens; t++)
	{
		while (string[index] == *delim_char)
			index++;

		letters = token_length(string + index, delim_char);

		ptr[t] = malloc(sizeof(char) * (letters + 1));
		if (!ptr[t])
		{
			for (index -= 1; index >= 0; index--)
				free(ptr[index]);
			free(ptr);
			return (NULL);
		}

		for (l = 0; l < letters; l++)
		{
			ptr[t][l] = string[index];
			index++;
		}

		ptr[t][l] = '\0';
	}
	ptr[t] = NULL;
	ptr[t + 1] = NULL;

	return (ptr);
}
