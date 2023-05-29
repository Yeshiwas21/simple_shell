#include "shell.h"

/**
 * _getenv - Gets the environmental variable from the PATH.
 * @var_name: Name of the environmental variable.
 *
 * Return: NULL, if the environmental variable does not exist
 *         Otherwise, a pointer to the environmental variable.
 */
char **_getenv(const char *var_name)
{
	int i = 0;
	int len = _strlen(var_name);

	while (environ[i] != NULL)
	{
		if (_strncmp(var_name, environ[i], len) == 0)
			return (&environ[i]);
		i++;
	}

	return (NULL);
}

/**
 * frees_env - Frees the the environment copy.
 */
void frees_env(void)
{
	int i = 0;

	while (environ[i] != NULL)
	{
		free(environ[i]);
		i++;
	}
	free(environ);
}