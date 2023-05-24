#include "shell.h"
/**
* print_env - prints the environment string to stdout
* @env: environ variabl
* Return: nothing
*/
void print_env(char **env)
{
	size_t i;

	i = 0;

	while (env[i])
	{
		write(STDOUT_FILENO, env[i], _strlen(env[i]));
		write(STDOUT_FILENO, "\n", 1);
		i++;
	}
}
