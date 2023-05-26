#include "shell.h"

/**
 * open_erro - If the file doesn't exist or lacks proper permissions, print
 * a cant open error.
 * @file_path: Path to the supposed file.
 *
 * Return: 127.
 */

int open_erro(char *file_path)
{
    char *error_message;
    char *hist_str;
    int message_len;

    hist_str = _itoa(hist);
    if (!hist_str)
        return 127;

    message_len = _strlen(name) + _strlen(hist_str) + _strlen(file_path) + 16;
    error_message = malloc(sizeof(char) * (message_len + 1));
    if (!error_message)
    {
        free(hist_str);
        return 127;
    }

    _strcpy(error_message, name);
    _strcat(error_message, ": ");
    _strcat(error_message, hist_str);
    _strcat(error_message, ": Can't open ");
    _strcat(error_message, file_path);
    _strcat(error_message, "\n");

    free(hist_str);
    write(STDERR_FILENO, error_message, message_len);
    free(error_message);
    return 127;
}

/**
 * run_file_commands - Attempts to run the commands stored
 * within.
 * @file_path: Path to the file.
 * @exe_ret: Return value of the last executed command.
 *
 * Return: If file couldn't be opened - 127.
 *   If malloc fails - -1.
 *   Otherwise the return value of the last command ran.
 */
int run_file_commands(char *file_path, int *exe_ret)
{
	ssize_t file, b_read;
	size_t i;
	unsigned int line_size = 0;
	unsigned int old_size = 120;
	char *line, **args, **front;
	char buffer[120];
	int ret;

	hist = 0;
	file = open(file_path, O_RDONLY);
	if (file == -1)
	{
		*exe_ret = open_erro(file_path);
		return (*exe_ret);
	}
	line = malloc(sizeof(char) * old_size);
	if (!line)
		return (-1);
	do {
		b_read = read(file, buffer, 119);
		if (b_read == 0 && line_size == 0)
			return (*exe_ret);
		buffer[b_read] = '\0';
		line_size += b_read;
		line = mem_realloc(line, old_size, line_size);
		_strcat(line, buffer);
		old_size = line_size;
	} while (b_read);

	for (i = 0; line[i] == '\n'; i++)
		line[i] = ' ';

	for (; i < line_size; i++)
	{
		if (line[i] == '\n')
		{
			line[i] = ';';
			for (i += 1; i < line_size && line[i] == '\n'; i++)
				line[i] = ' ';
		}
	}

	replace_var(&line, exe_ret);
	handles_line(&line, line_size);
	args = token_strtok(line, " ");
	free(line);
	if (!args)
		return (0);

	if (checks_arguments(args) != 0)
	{
		*exe_ret = 2;
		free_arguments(args, args);
		return (*exe_ret);
	}

	front = args;
	i = 0;

	while (args[i])
	{
		if (_strncmp(args[i], ";", 1) == 0)
		{
			free(args[i]);
			args[i] = NULL;
			ret = calls_arguments(args, front, exe_ret);
			args = &args[++i];
			i = 0;
		}
		else
		{
			i++;
		}
	}

	ret = calls_arguments(args, front, exe_ret);

	free(front);
	return (ret);
}