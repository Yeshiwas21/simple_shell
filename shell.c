#include "shell.h"
void execuut(char *path, char **argv, char **arg, int linec, char **env);
/**
 * main - main entrance
 * @ac: argument count
 * @argv: array of argument pointers
 * @env: environ parameter
 * Return: always success 0
 */
int main(int ac, char **argv, char **env)
{
	char *line;
	char *line_cpy;
	char *token;
	pid_t pid;
	ssize_t j;
	int k;
	const char *delim;
	int w;
	int status;
	int no_token;
	size_t n;
	int linec;
	char *path;
	char **arg;
	int ex;

	line = NULL;
	line_cpy = NULL;
	token = NULL;
	path = NULL;
	n = 0;
	ex = 0;
	linec = 0;
	no_token = 0;
	delim = " \n";

	(void)ac;

	while (1)
	{
		linec++;
		if (isatty(STDIN_FILENO))
		{
			write(1, "($) ", 4);
		}
		j = getline(&line, &n, stdin);
		if (j == -1)
		{
			if (isatty(STDIN_FILENO))
			{
				write(1, "\n", 1);
			}
			free(line);
			exit(0);
		}
		line_cpy = malloc(sizeof(char) * (j + 1));
		if (line_cpy == NULL)
		{
			free(line_cpy);
			exit(EXIT_FAILURE);
		}
		_strcpy(line_cpy, line);
		token = strtok(line, delim);
		while (token != NULL)
		{
			no_token++;
			token = strtok(NULL, delim);
		}
		no_token++;
		arg = malloc(sizeof(char *) * no_token);

		if (arg == NULL)
		{
			exit(EXIT_FAILURE);
		}
		token = strtok(line_cpy, delim);

		for (k = 0; token != NULL; k++)
		{
			arg[k] = malloc(sizeof(char) * (_strlen(token) + 1));

			if (arg[k] == NULL)
			{
				exit(-1);
			}
			_strcpy(arg[k], token);

			token = strtok(NULL, delim);
		}
		arg[k] = NULL;
		if (_strncmp(line, "exit\n", 5) == 0 && arg[1] == NULL)
		{
			free(line);
			free(line_cpy);
			free(arg);
			exit(ex);
		}
		if (_strncmp(line, "env\n", 4) == 0)
		{
			print_env(env);
			continue;
		}

		if (arg[0] == NULL)
			continue;
		else
		{
			path = get_cmdpath(arg[0]);
			if (!path)
			{
				printf("%s: %d: %s: not found\n", argv[0], linec, arg[0]);
				ex = 127;
				continue;
			}
			else
			{
				pid = fork();
				if (pid == -1)
				{
					write(2, "fork failed\n", 13);
					break;
				}
				else if (pid == 0)
				{
					execuut(path, argv, arg, linec, env);
				}
				else
				{
					wait(&status);
					if (WIFEXITED(status) && WEXITSTATUS(status) != 0)
						return (WEXITSTATUS(status));
				}
			}
		}
		no_token = 0;
	}
	free(line_cpy);
	for (w = 0; w < no_token - 1; w++)
	{
		free(arg[w]);
	}
	free(arg);
	return (EXIT_SUCCESS);
}
/**
 * execuut - execute command
 * @path: the command path
 * @argv: the command and the argument for the file
 * @arg: the command and args
 * @linec: counter
 * @env: environ
 * Return: none
 */
void execuut(char *path, char **argv, char **arg, int linec, char **env)
{
	char *mycmd;
	int ret;

	mycmd = path;
	ret = execve(mycmd, arg, env);
	if (ret == -1)
	{
		printf("%s: %d: %s: not found\n", argv[0], linec, arg[0]);
		exit(errno);
	}
}
