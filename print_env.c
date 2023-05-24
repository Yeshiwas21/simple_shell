#include "shell.h"
/**
* print_env - prints the environment string to stdout
*
* Return: nothing
*/
void print_env(void)
{
	size_t i;

	i = 0;

	while (environ[i])
	{
		write(STDOUT_FILENO, environ[i], _strlen(environ[i]));
		write(STDOUT_FILENO, "\n", 1);
		i++;
	}
}
