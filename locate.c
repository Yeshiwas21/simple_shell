#include "shell.h"

/**
 * get_command_location - Locates a command in the PATH.
 * @command: The command to locate.
 *
 * Return: If an error occurs or the command cannot be located - NULL.
 *         Otherwise - the full pathname of the command.
 */
char *get_command_location(char *command)
{
	char **path, *temp;
	list_t *dirs_list, *head_ptr;
	struct stat st;

	path = _getenv("PATH");
	if (!path || !(*path))
		return (NULL);

	dirs_list = get_dir_path(*path + 5);
	head_ptr = dirs_list;

	while (dirs_list)
	{
		temp = malloc(_strlen(dirs_list->dir_path) + _strlen(command) + 2);
		if (!temp)
			return (NULL);

		_strcpy(temp, dirs_list->dir_path);
		_strcat(temp, "/");
		_strcat(temp, command);

		if (stat(temp, &st) == 0)
		{
			free_list(head_ptr);
			return (temp);
		}

		dirs_list = dirs_list->next;
		free(temp);
	}

	free_list(head_ptr);

	return (NULL);
}

/**
 * fill_dir_path - Copies path and replaces leading/sandwiched/trailing
 *   colons (:) with current working directory.
 * @dir_path: The colon-separated list of directories.
 *
 * Return: A copy of path with any leading/sandwiched/trailing colons replaced
 *   with the current working directory.
 */
char *fill_dir_path(char *dir_path)
{
	int i, length = 0;
	char *copy_path, *pwd;

	pwd = *(_getenv("PWD")) + 4;
	for (i = 0; dir_path[i]; i++)
	{
		if (dir_path[i] == ':')
		{
			if (dir_path[i + 1] == ':' || i == 0 || dir_path[i + 1] == '\0')
				length += _strlen(pwd) + 1;
			else
				length++;
		}
		else
			length++;
	}
	copy_path = malloc(sizeof(char) * (length + 1));
	if (!copy_path)
		return (NULL);
	copy_path[0] = '\0';
	for (i = 0; dir_path[i]; i++)
	{
		if (dir_path[i] == ':')
		{
			if (i == 0)
			{
				_strcat(copy_path, pwd);
				_strcat(copy_path, ":");
			}
			else if (dir_path[i + 1] == ':' || dir_path[i + 1] == '\0')
			{
				_strcat(copy_path, ":");
				_strcat(copy_path, pwd);
			}
			else
				_strcat(copy_path, ":");
		}
		else
		{
			_strncat(copy_path, &dir_path[i], 1);
		}
	}
	return (copy_path);
}

/**
 * get_dir_path - Tokenizes a colon-separated list of
 *                directories into a list_s linked list.
 * @dir_list: The colon-separated list of directories.
 *
 * Return: A pointer to the initialized linked list.
 */
list_t *get_dir_path(char *dir_list)
{
	int i = 0;
	char **dirs_list, *copy_path;
	list_t *head_ptr = NULL;

	copy_path = fill_dir_path(dir_list);
	if (!copy_path)
		return (NULL);
	dirs_list = token_strtok(copy_path, ":");
	free(copy_path);
	if (!dirs_list)
		return (NULL);

	while (dirs_list[i])
	{
		if (add_node_to_end(&head_ptr, dirs_list[i]) == NULL)
		{
			free_list(head_ptr);
			free(dirs_list);
			return (NULL);
		}
		i++;
	}

	free(dirs_list);

	return (head_ptr);
}
