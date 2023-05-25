#include <stddef.h>
#include "shell.h"
/**
 * get_env - finds the value PATH environment variable
 * Return: pointer to the path variable
 */
char *get_env(void)
{
	int x;

	char **env = environ, *path = NULL;

	x = 0;

	while (*env)
	{
		if (_strncmp(*env, "PATH=", 5) == 0)
		{
			path = *env;
			while (*path && x < 5)
			{
				path++;
				x++;
			}
			return (path);
		}
		env++;
	}
	return (NULL);
}
/**
 * get_cmdpath - finds the command path
 * @cmd: input command
 * Return: a pointer to the path
 */
char *get_cmdpath(char *cmd)
{
	char *path, *path_cpy, *token, *cmd_path;
	int cmd_len, dir_len;
	struct stat buf;
	int i;
	char *temp;

	path = get_env();
	if (path)
	{
		path_cpy = malloc(sizeof(char) * (_strlen(path) + 1));
		path_cpy = _strcpy(path_cpy, path);
		cmd_len = _strlen(cmd);
		token = strtok(path_cpy, ":");
		while (token != NULL)
		{
			dir_len = _strlen(token);
			cmd_path = malloc(dir_len + cmd_len + 2);
			_strcpy(cmd_path, token);
			_strcat(cmd_path, "/");
			_strcat(cmd_path, cmd);
			_strcat(cmd_path, "\0");
			if (stat(cmd_path, &buf) == 0)
			{
				free(path_cpy);
				return (cmd_path);
			}
			else
			{
				free(cmd_path);
				token = strtok(NULL, ":");
			}
		}
		free(path_cpy);
		if (stat(cmd, &buf) == 0)
		{
			return (cmd);
		}
		return (NULL);
	}
	else
	{
		for (i = 0; path[i] != '\0'; i++)
		{
			temp = "path[i]";
			if (_strcmp(temp, "/") == 0)
			{
				return (path);
			}
		}
	}
	return (NULL);
}
