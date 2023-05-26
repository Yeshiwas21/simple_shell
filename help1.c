#include "shell.h"

/**
 * retrieve_arguments - Gets a command from standard input.
 * @input_command: A buffer to store the command.
 * @execution_return: The return value of the last executed command.
 *
 * Return: If an error occurs - NULL.
 *         Otherwise - a pointer to the stored command.
 */
char *retrieve_arguments(char *command_input, int *execution_return)
{
    size_t buffer_size = 0;
    ssize_t read_bytes;
    char *prompt = "$ ";

    if (command_input)
        free(command_input);

    read_bytes = read_input(&command_input, &buffer_size, STDIN_FILENO);
    if (read_bytes == -1)
        return NULL;
    if (read_bytes == 1)
    {
        hist++;
        if (isatty(STDIN_FILENO))
            write(STDOUT_FILENO, prompt, 2);
        return retrieve_arguments(command_input, execution_return);
    }

    command_input[read_bytes - 1] = '\0';
    replace_var(&command_input, execution_return);
    handles_line(&command_input, read_bytes);

    return command_input;
}

/**
 * calls_arguments - Partitions operators from commands
 * @arguments: Array of arguments.
 * @front_ptr: Double pointer to the beginning of arguments.
 * @execution_return: The return value of the parent process' last executed command.
 *
 * Return: The return value of the last executed command.
 */
int calls_arguments(char **arguments, char **front_ptr, int *execution_return)
{
	int ret, index = 0;

	if (!arguments[0])
		return (*execution_return);

	while (arguments[index])
	{
		if (_strncmp(arguments[index], "||", 2) == 0)
		{
			free(arguments[index]);
			arguments[index] = NULL;
			arguments = replace_aliases(arguments);
			ret = runs_arguments(arguments, front_ptr, execution_return);

			if (*execution_return != 0)
			{
				arguments = &arguments[++index];
				index = 0;
			}
			else
			{
				while (arguments[index])
					free(arguments[index++]);
				return ret;
			}
		}
		else if (_strncmp(arguments[index], "&&", 2) == 0)
		{
			free(arguments[index]);
			arguments[index] = NULL;
			arguments = replace_aliases(arguments);
			ret = runs_arguments(arguments, front_ptr, execution_return);

			if (*execution_return == 0)
			{
				arguments = &arguments[++index];
				index = 0;
			}
			else
			{
				while (arguments[index])
					free(arguments[index++]);
				return ret;
			}
		}

		index++;
	}

	arguments = replace_aliases(arguments);
	ret = runs_arguments(arguments, front_ptr, execution_return);
	return ret;
}

/**
 * runs_arguments - Calls the execution of a command.
 * @arguments: Array of arguments.
 * @front_ptr: Double pointer to the beginning of arguments.
 * @execution_return: The return value of the parent process' last executed command.
 *
 * Return: The return value of the last executed command.
 */
int runs_arguments(char **arguments, char **front_ptr, int *execution_return)
{
	int ret, i;
	int (*builtin)(char **arguments, char **front_ptr);

	builtin = get_command(arguments[0]);

	if (builtin)
	{
		ret = builtin(arguments + 1, front_ptr);
		if (ret != EXIT)
			*execution_return = ret;
	}
	else
	{
		*execution_return = executeCustomCommand(arguments, front_ptr);
		ret = *execution_return;
	}

	hist++;

	for (i = 0; arguments[i]; i++)
		free(arguments[i]);

	return (ret);
}

/**
 * handles_arguments - Gets, calls, and runs the execution of a command.
 * @execution_return: The return value of the parent process' last executed command.
 *
 * Return: END_OF_FILE (-2), if an end-of-file is read
 *         -1, if the input cannot be tokenized
 *         O/w - The exit value of the last executed command.
 */
int handles_arguments(int *execution_return)
{
	int ret = 0, index;
	char **arguments, *line = NULL, **front_ptr;

	line = retrieve_arguments(line, execution_return);
	if (!line)
		return (END_OF_FILE);

	arguments = token_strtok(line, " ");
	free(line);
	if (!arguments)
		return (ret);
	if (checks_arguments(arguments) != 0)
	{
		*execution_return = 2;
		free_arguments(arguments, arguments);
		return (*execution_return);
	}
	front_ptr = arguments;

	for (index = 0; arguments[index]; index++)
	{
		if (_strncmp(arguments[index], ";", 1) == 0)
		{
			free(arguments[index]);
			arguments[index] = NULL;
			ret = calls_arguments(arguments, front_ptr, execution_return);
			arguments = &arguments[++index];
			index = 0;
		}
	}
	if (arguments)
		ret = calls_arguments(arguments, front_ptr, execution_return);

	free(front_ptr);
	return (ret);
}

/**
 * checks_arguments - Checks any leading ';', ';;', '&&', or '||'.
 * @arguments: Double pointer to tokenized commands and arguments.
 *
 * Return: 2, If a ';', '&&', or '||' is placed at an invalid position
 *   Otherwise - 0.
 */
int checks_arguments(char **arguments)
{
	size_t i;
	char *cur, *nex;

	for (i = 0; arguments[i]; i++)
	{
		cur = arguments[i];
		if (cur[0] == ';' || cur[0] == '&' || cur[0] == '|')
		{
			if (i == 0 || cur[1] == ';')
				return (write_error(&arguments[i], 2));
			nex = arguments[i + 1];
			if (nex && (nex[0] == ';' || nex[0] == '&' || nex[0] == '|'))
				return (write_error(&arguments[i + 1], 2));
		}
	}
	return (0);
}
