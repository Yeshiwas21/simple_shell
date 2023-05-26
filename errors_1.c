#include "shell.h"

/**
 * write_error - Writes a custom error message to stderr
 * @arguments: Array of arguments.
 * @error_val: The error value.
 *
 * Return: The error value.
 */
int write_error(char **arguments, int error_val)
{
	char *error;

	switch (error_val)
	{
	case -1:
		error = error_for_env(arguments);
		break;
	case 1:
		error = error_1_alias(arguments);
		break;
	case 2:
		if (*(arguments[0]) == 'e')
			error = error_for_exit(++arguments);
		else if (arguments[0][0] == ';' || arguments[0][0] == '&' || arguments[0][0] == '|')
			error = error_for_syntax(arguments);
		else
			error = error_for_cd(arguments);
		break;
	case 126:
		error = error_for_126(arguments);
		break;
	case 127:
		error = error_for_127(arguments);
		break;
	}
	write(STDERR_FILENO, error, _strlen(error));

	if (error)
		free(error);
	return (error_val);

}
/**
 * error_for_env - Creates an error message for print_env.
 * @arguments: An array of arguments.
 *
 * Return: The error string.
 */
char *error_for_env(char **arguments)
{
    char *error_msg, *hist_str;
    int len;

    hist_str = _itoa(hist);
    if (!hist_str)
        return NULL;

    arguments--;
    len = _strlen(name) + _strlen(hist_str) + _strlen(arguments[0]) + 45;
    error_msg = malloc(sizeof(char) * (len + 1));
    if (!error_msg)
    {
        free(hist_str);
        return NULL;
    }

    _strcpy(error_msg, name);
    _strcat(error_msg, ": ");
    _strcat(error_msg, hist_str);
    _strcat(error_msg, ": ");
    _strcat(error_msg, arguments[0]);
    _strcat(error_msg, ": Unable to add/remove from environment\n");

    free(hist_str);
    return error_msg;
}

/**
 * error_1_alias - Creates an error message for all_alias errors.
 * @arguments: An array of arguments passed to the command.
 *
 * Return: The error string.
 */
char *error_1_alias(char **arguments)
{
	char *error;
	int len;

	len = _strlen(name) + _strlen(arguments[0]) + 13;
	error = malloc(sizeof(char) * (len + 1));
	if (!error)
		return (NULL);

	_strcpy(error, "alias: ");
	_strcat(error, arguments[0]);
	_strcat(error, " not found\n");

	return (error);
}

/**
 * error_for_exit - Creates an error message for shell_exit errors.
 * @arguments: Array of arguments passed to the command.
 *
 * Return: The error string.
 */
char *error_for_exit(char **arguments)
{
	char *error, *hist_str;
	int len;

	hist_str = _itoa(hist);
	if (!hist_str)
		return (NULL);

	len = _strlen(name) + _strlen(hist_str) + _strlen(arguments[0]) + 27;
	error = malloc(sizeof(char) * (len + 1));
	if (!error)
	{
		free(hist_str);
		return (NULL);
	}

	_strcpy(error, name);
	_strcat(error, ": ");
	_strcat(error, hist_str);
	_strcat(error, ": exit: Illegal number: ");
	_strcat(error, arguments[0]);
	_strcat(error, "\n");

	free(hist_str);
	return (error);
}

/**
 * error_for_cd - Creates an error message for shellby_cd errors.
 * @arguments: An array of arguments passed to the command.
 *
 * Return: The error string.
 */
char *error_for_cd(char **arguments)
{
	char *error, *hist_str;
	int len;

	hist_str = _itoa(hist);
	if (!hist_str)
		return (NULL);

	if (arguments[0][0] == '-')
		arguments[0][2] = '\0';
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
	if (arguments[0][0] == '-')
		_strcat(error, ": cd: Illegal option ");
	else
		_strcat(error, ": cd: can't cd to ");
	_strcat(error, arguments[0]);
	_strcat(error, "\n");

	free(hist_str);
	return (error);
}
