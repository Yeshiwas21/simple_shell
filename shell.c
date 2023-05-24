#include "shell.h"
void execuut(char *path, char **argv, char **arg, int linec);
/**
 * main - main entrance
 * @ac: argument count
 * @argv: arrray of argument pointer
 * Return: always success 0
 */
int main(int ac, char **argv)
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

	line = NULL;
	line_cpy = NULL;
	token = NULL;
	path = NULL;
	n = 0;
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
			exit(0);
		}
		if (_strncmp(line, "exit\n", 5) == 0)
		{
			exit(0);
		}
		if (_strncmp(line, "env\n", 4) == 0)
		{
			print_env();
		}
		line_cpy = malloc(sizeof(char) * (j + 1));
		if (line_cpy == NULL)
		{
			return (-1);
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
			free(line_cpy);
			return (-1);
		}
		token = strtok(line_cpy, delim);

		for (k = 0; token != NULL; k++)
		{
			arg[k] = malloc(sizeof(char) * (_strlen(token) + 1));

			if (arg[k] == NULL)
			{
				free(line_cpy);
				free(arg);
				return (-1);
			}
			_strcpy(arg[k], token);

			token = strtok(NULL, delim);
		}
		arg[k] = NULL;

		if (arg[0] == NULL)
			continue;

		path = get_cmdpath(arg[0]);

		if (!path)
		{
			printf("%s: %d: %s: not found\n", argv[0], linec, arg[0]);
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
			execuut(path, argv, arg, linec);
		}
		else
		{
			wait(&status);
			if (WIFEXITED(status) && WEXITSTATUS(status) != 0)
			return (WEXITSTATUS(status));
		}
		no_token = 0;
		}
	}
	free(line_cpy);
	for (w = 0; w < no_token - 1; w++)
	{
		free(argv[w]);
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
 * Return: none
 */
void execuut(char *path, char **argv, char **arg, int linec)
{
	char *mycmd;
	int ret;

	mycmd = path;
	ret = execve(mycmd, arg, NULL);
	if (ret == -1)
	{
		printf("%s: %d: %s: not found\n", argv[0], linec, arg[0]);
		exit(errno);
	}
}
