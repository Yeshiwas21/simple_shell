#include "shell.h"
/**
* print_env - prints the environment string to stdout
* @env: environ variabl
* Return: nothing
*/
void print_env(char **env)
{
int i;
for (i = 0; env[i] != NULL; i++)
{
size_t len = _strlen(env[i]);
write(STDOUT_FILENO, env[i], len);
write(STDOUT_FILENO, "\n", 1);
}
}
