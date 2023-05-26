#include "shell.h"

/**
 * get_current_pid - Gets the current process ID.
 * Description: Opens the stat file, a space-delimited file containing
 *              information about the current process. The PID is the
 *              first word in the file. The function reads the PID into
 *              a buffer and replace the space at the end with a \0 byte.
 *
 * Return: Current pid or NULL on failure
 */
char *get_current_pid(void)
{
	size_t i = 0;
	char *buffer;
	ssize_t file;

	file = open("/proc/self/stat", O_RDONLY);
	if (file == -1)
	{
		perror("Cant read file");
		return (NULL);
	}
	buffer = malloc(120);
	if (!buffer)
	{
		close(file);
		return (NULL);
	}
	read(file, buffer, 120);
	while (buffer[i] != ' ')
		i++;
	buffer[i] = '\0';

	close(file);
	return (buffer);
}

/**
 * get_env_value - Gets the value of the environmental variable
 * @env_var: The environmental variable.
 * @env_length: The Length of the environmental variable
 *
 * Return: empty string, if the variable is not found
 *         Otherwise - the value of the environmental variable.
 *
 * Description: Variables are stored in the format VARIABLE=VALUE.
 */
char *get_env_value(char *env_var, int env_length)
{
	char **var_addrress;
	char *new_char = NULL, *temp, *var;

	var = malloc(env_length + 1);
	if (!var)
		return (NULL);
	var[0] = '\0';
	_strncat(var, env_var, env_length);

	var_addrress = _getenv(var);
	free(var);
	if (var_addrress)
	{
		temp = *var_addrress;
		while (*temp != '=')
			temp++;
		temp++;
		new_char = malloc(_strlen(temp) + 1);
		if (new_char)
			_strcpy(new_char, temp);
	}

	return (new_char);
}

/**
 * variable_replacement - Handles variable new_char.
 * @arguments: A double pointer containing the command and arguments.
 * @execution_return: A pointer to the return value of the last executed command.
 *
 * Description: Replaces $$ with the current PID, $? with the return value
 *              of the last executed program, and envrionmental variables
 *              preceded by $ with their corresponding value.
 */
void replace_var(char **arguments, int *execution_return)
{
	int j, k = 0, len;
	char *new_char = NULL, *old_args = NULL, *new_args;

	old_args = *arguments;
	for (j = 0; old_args[j]; j++)
	{
		if (old_args[j] == '$' && old_args[j + 1] &&
		    old_args[j + 1] != ' ')
		{
			if (old_args[j + 1] == '$')
			{
				new_char = get_current_pid();
				k = j + 2;
			}
			else if (old_args[j + 1] == '?')
			{
				new_char = _itoa(*execution_return);
				k = j + 2;
			}
			else if (old_args[j + 1])
			{
				/* extract the variable name to search for */
				for (k = j + 1; old_args[k] &&
					     old_args[k] != '$' &&
					     old_args[k] != ' '; k++)
					;
				len = k - (j + 1);
				new_char = get_env_value(&old_args[j + 1], len);
			}
			new_args = malloc(j + _strlen(new_char)
					  + _strlen(&old_args[k]) + 1);
			if (!arguments)
				return;
			new_args[0] = '\0';
			_strncat(new_args, old_args, j);
			if (new_char)
			{
				_strcat(new_args, new_char);
				free(new_char);
				new_char = NULL;
			}
			_strcat(new_args, &old_args[k]);
			free(old_args);
			*arguments = new_args;
			old_args = new_args;
			j = -1;
		}
	}
}

/**
 * free_arguments - Frees up the  memory taken by arguments
 * @arguments: A null-terminated double pointer containing arguments
 * @front_ptr: A double pointer to the env_var of arguments.
 */
void free_arguments(char **arguments, char **front_ptr)
{
	size_t i;

	for (i = 0; arguments[i] || arguments[i + 1]; i++)
		free(arguments[i]);

	free(front_ptr);
}
