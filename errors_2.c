#include "shell.h"

/**
 * error_for_syntax - Creates an error message for syntax errors.
 * @args: Array of arguments passed to the command.
 *
 * Return: The error string.
 */
char *error_for_syntax(char **arguments)
{
    char *error;
    char *hist_str;
    int len;

    hist_str = _itoa(hist);
    if (!hist_str)
        return NULL;

    len = _strlen(name) + _strlen(hist_str) + _strlen(arguments[0]) + 33;
    error = malloc(sizeof(char) * (len + 1));
    if (!error)
    {
        free(hist_str);
        return NULL;
    }

    _strcpy(error, name);
    _strcat(error, ": ");
    _strcat(error, hist_str);
    _strcat(error, ": Syntax error: \"");
    _strcat(error, arguments[0]);
    _strcat(error, "\" unexpected\n");

    free(hist_str);
    return error;
}

/**
 * error_for_126 - Creates an error message for permission denied failures.
 * @arguments: Array of arguments passed to the command.
 *
 * Return: The error string.
 */
char *error_for_126(char **arguments)
{
	char *error, *hist_str;
	int len;

	hist_str = _itoa(hist);
	if (!hist_str)
		return (NULL);

	len = _strlen(name) + _strlen(hist_str) + _strlen(arguments[0]) + 24;
	error = malloc(sizeof(char) * (len + 1));
	if (!error)
	{
		free(hist_str);
		return (NULL);
	}

	_strcpy(error, name);
	_strcat(error, ": ");
	_strcat(error, hist_str);
	_strcat(error, ": ");
	_strcat(error, arguments[0]);
	_strcat(error, ": Permission denied\n");

	free(hist_str);
	return (error);
}

/**
 * error_for_127 - Creates an error message for command not found.
 * @arguments: Array of arguments passed to the command.
 *
 * Return: The error string.
 */
char *error_for_127(char **arguments)
{
	char *error, *hist_str;
	int len;

	hist_str = _itoa(hist);
	if (!hist_str)
		return (NULL);

	len = _strlen(name) + _strlen(hist_str) + _strlen(arguments[0]) + 16;
	error = malloc(sizeof(char) * (len + 1));
	if (!error)
	{
		free(hist_str);
		return (NULL);
	}

	_strcpy(error, name);
	_strcat(error, ": ");
	_strcat(error, hist_str);
	_strcat(error, ": ");
	_strcat(error, arguments[0]);
	_strcat(error, ": not found\n");

	free(hist_str);
	return (error);
}