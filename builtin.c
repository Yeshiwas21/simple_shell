#include "shell.h"

/**
 * get_command - Matches a command with builtin function
 * @command: A command to be matched
 *
 * Return: A function pointer to the corresponding builtin.
 */
int (*get_command(char *command))(char **arguments, char **front_ptr)
{
	builtin_t funcs[] = {
		{ "cd", change_dir },
		{ "env", print_env },
		{ "setenv", _setenv },
		{ "unsetenv", _unsetenv },
		{ "exit", exit_shell },
		{ "alias", all_alias },
		{ "help", shell_help },
		{ NULL, NULL }
	};
	int i = 0;

	while (funcs[i].name != NULL)
	{
		if (_strcmp(funcs[i].name, command) == 0)
			break;
		i++;
	}

	return funcs[i].f;
}

/**
 * change_dir - Changes the current director.
 * @arguments: Array of arguments
 * @front_ptr: A double pointer to the beginning of arguments
 *
 * Return: 2, if the given string is not a directory
 *         -1, If an error occurs
 *         0, Otherwise
 */
int change_dir(char **arguments, char __attribute__((__unused__)) **front_ptr)
{
    char **dir_info, *newline = "\n";
    char *old_pwd = NULL, *current_pwd = NULL;
    struct stat dir;

    old_pwd = getcwd(old_pwd, 0);
    if (!old_pwd)
        return -1;

    if (arguments[0])
    {
        if (*arguments[0] == '-' || _strcmp(arguments[0], "--") == 0)
        {
            if ((arguments[0][1] == '-' && arguments[0][2] == '\0') || arguments[0][1] == '\0')
            {
                if (_getenv("OLDPWD") != NULL)
                    chdir(*_getenv("OLDPWD") + 7);
            }
            else
            {
                free(old_pwd);
                return write_error(arguments, 2);
            }
        }
        else
        {
            if (stat(arguments[0], &dir) == 0 && S_ISDIR(dir.st_mode) && (dir.st_mode & S_IXUSR) != 0)
                chdir(arguments[0]);
            else
            {
                free(old_pwd);
                return write_error(arguments, 2);
            }
        }
    }
    else
    {
        if (_getenv("HOME") != NULL)
            chdir(*(_getenv("HOME")) + 5);
    }

    current_pwd = getcwd(current_pwd, 0);
    if (!current_pwd)
        return -1;

    dir_info = malloc(sizeof(char *) * 2);
    if (!dir_info)
        return -1;

    dir_info[0] = "OLDPWD";
    dir_info[1] = old_pwd;
    if (_setenv(dir_info, dir_info) == -1)
        return -1;

    dir_info[0] = "PWD";
    dir_info[1] = current_pwd;
    if (_setenv(dir_info, dir_info) == -1)
        return -1;

    if (arguments[0] && arguments[0][0] == '-' && arguments[0][1] != '-')
    {
        write(STDOUT_FILENO, current_pwd, _strlen(current_pwd));
        write(STDOUT_FILENO, newline, 1);
    }

    free(old_pwd);
    free(current_pwd);
    free(dir_info);
    return 0;
}

/**
 * exit_shell - Causes to terminate rhe shell.
 * @arguments: An array of arguments with the exit value.
 * @front_ptr: A double pointer to the beginning of arguments
 *
 * Return: 3, ff there are no arguments
 *         2, If the given exit value is invalid
 *         O/w - exits with the given status value.
 *
 * Description: when returning -3, the program exits back to the main function
 */
int exit_shell(char **arguments, char **front_ptr)
{
	int i, int_length = 10;
    unsigned int num = 0, max = 1U << (sizeof(int) * 8 - 1);

    if (arguments[0] != NULL)
    {
        if (arguments[0][0] == '+')
        {
            i = 1;
            int_length++;
        }
        for (; arguments[0][i]; i++)
        {
            if (i <= int_length && arguments[0][i] >= '0' && arguments[0][i] <= '9')
                num = (num * 10) + (arguments[0][i] - '0');
            else
                return write_error(--arguments, 2);
        }
    }
    else
    {
        return -3;
    }

    if (num > (max - 1))
        return write_error(--arguments, 2);

    arguments--;
    free_arguments(arguments, front_ptr);
    frees_env();
    frees_alias_list(aliases);
    exit(num);
}

/**
 * shell_help - Displays information about shellby builtin commands.
 * @arguments: An array of arguments.
 * @front_ptr: A pointer to the beginning of arguments.
 *
 * Return: If an error occurs - -1.
 *         Otherwise - 0.
 */
 
int shell_help(char **arguments, char __attribute__((__unused__)) **front_ptr)
{
	char *name = "shellby: help: no help topics match";

	if (!arguments[0])
	{
		help_for_all();
	}
	else
	{
		char *command = arguments[0];
		switch (_strcmp(command, "alias"))
		{
			case 0:
				help_for_alias();
				break;
			case 1:
				help_for_cd();
				break;
			case 2:
				help_for_exit();
				break;
			case 3:
				help_all_env();
				break;
			case 4:
				help_set_env();
				break;
			case 5:
				help_unset_env();
				break;
			case 6:
				help_for_help();
				break;
			default:
				write(STDERR_FILENO, name, _strlen(name));
		}
	}

	return (0);
}