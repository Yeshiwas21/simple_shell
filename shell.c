#include "shell.h"

/**
 * handle_signal - Prints a new prompt.
 * @signal_number: The signal number.
 */
void handle_signal(int signal_number)
{
    const char *new_prompt = "\n$ ";

    (void)signal_number;
    signal(SIGINT, handle_signal);
    write(STDOUT_FILENO, new_prompt, 3);
}

/**
 * executeCustomCommand - Executes a command in a child process
 * @arguments: An array of arguments.
 * @front_ptr: A double pointer to the beginning of args.
 *
 * Return: If an error occurs - a corresponding error code.
 *         O/w - The exit value of the last executed command.
 */
int executeCustomCommand(char **arguments, char **front_ptr)
{
    pid_t child_pid;
    int status, flag = 0, ret = 0;
    char *command = arguments[0];

    flag = (command[0] != '/' && command[0] != '.');

    if (flag)
        command = get_command_location(command);

    if (!command || access(command, F_OK) == -1)
    {
        ret = (errno == EACCES) ? write_error(arguments, 126) : write_error(arguments, 127);
    }
    else
    {
        child_pid = fork();
        if (child_pid == -1)
        {
            if (flag)
                free(command);
            perror("Error child:");
            return 1;
        }
        if (child_pid == 0)
        {
            execve(command, arguments, environ);
            if (errno == EACCES)
                ret = write_error(arguments, 126);
            frees_env();
            free_arguments(arguments, front_ptr);
            frees_alias_list(aliases);
            _exit(ret);
        }
        else
        {
            wait(&status);
            ret = WEXITSTATUS(status);
        }
    }

    if (flag)
        free(command);
    return ret;
}

/**
 * main - Runs a simple UNIX command interpreter.
 * @argc: The number of arguments.
 * @argv: An array of arguments.
 *
 * Return: The return value of the last executed command.
 */
int main(int argc, char *argv[])
{
	int ret = 0, retn;
	int *exe_ret = &retn;
	char *prompt = "$ ", *new_line = "\n";

	name = argv[0];
	hist = 1;
	aliases = NULL;
	signal(SIGINT, handle_signal);

	*exe_ret = 0;
	environ = _copyenv();
	if (!environ)
		exit(-100);

	if (argc != 1)
	{
		ret = run_file_commands(argv[1], exe_ret);
		frees_env();
		frees_alias_list(aliases);
		return (*exe_ret);
	}

	if (!isatty(STDIN_FILENO))
	{
		while (ret != END_OF_FILE && ret != EXIT)
			ret = handles_arguments(exe_ret);
		frees_env();
		frees_alias_list(aliases);
		return (*exe_ret);
	}

	while (1)
	{
		write(STDOUT_FILENO, prompt, 2);
		ret = handles_arguments(exe_ret);
		if (ret == END_OF_FILE || ret == EXIT)
		{
			if (ret == END_OF_FILE)
				write(STDOUT_FILENO, new_line, 1);
			frees_env();
			frees_alias_list(aliases);
			exit(*exe_ret);
		}
	}

	frees_env();
	frees_alias_list(aliases);
	return (*exe_ret);
}
