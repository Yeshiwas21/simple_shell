#include "shell.h"

/**
 * print_env - Prints the current environment.
 * @arguments: Array of arguments given to the shell.
 * @front_ptr: A double pointer to the beginning of arguments
 *
 * Return: 1, If an error occurs.
 *   Otherwise - 0.
 *
 * Description: Prints one environment variable per line in the
 *              format 'variable'='value'.
 */
int print_env(char **arguments, char __attribute__((__unused__)) **front_ptr)
{
	int i;
	char number_of_char = '\n';

	if (!environ)
		return (-1);

	for (i = 0; environ[i]; i++)
	{
		write(STDOUT_FILENO, environ[i], _strlen(environ[i]));
		write(STDOUT_FILENO, &number_of_char, 1);
	}

	(void)arguments;
	return (0);
}

/**
 * _setenv - Changes or adds an environmental variable to the PATH.
 * @arguments: Array of arguments passed to the shell.
 * @front_ptr: A double pointer to the beginning of arguments.
 *
 * Description: arguments[1]- the name of the new or existing PATH variable
 *              arguments[2] - is the value to set the new or changed variable
 *
 * Return: 1, If an error occurs
 *         0, Otherwise
 */
int _setenv(char **arguments, char __attribute__((__unused__)) **front_ptr)
{
    char **env_var = NULL;
    char **new_environment = NULL;
    char *new_value = NULL;
    size_t env_size = 0;
    int idx;

    if (!arguments[0] || !arguments[1])
        return write_error(arguments, -1);

    new_value = malloc(_strlen(arguments[0]) + 1 + _strlen(arguments[1]) + 1);
    if (!new_value)
        return write_error(arguments, -1);

    _strcpy(new_value, arguments[0]);
    _strcat(new_value, "=");
    _strcat(new_value, arguments[1]);

    env_var = _getenv(arguments[0]);
    if (env_var)
    {
        free(*env_var);
        *env_var = new_value;
        return 0;
    }

    for (env_size = 0; environ[env_size]; env_size++)
        ;

    new_environment = malloc(sizeof(char *) * (env_size + 2));
    if (!new_environment)
    {
        free(new_value);
        return write_error(arguments, -1);
    }

    for (idx = 0; environ[idx]; idx++)
        new_environment[idx] = environ[idx];

    free(environ);
    environ = new_environment;
    environ[idx] = new_value;
    environ[idx + 1] = NULL;

    return 0;
}

/**
 * _unsetenv - Deletes an environmental variable from the PATH.
 * @arguments: Array of arguments give to the shell
 * @front_ptr: A double pointer to the beginning of arguments
 *
 * Description: arguments[1]- the PATH variable to be removed.
 *
 * Return: 1, if an error occurs.
 *         Otherwise - 0.
 */
int _unsetenv(char **arguments, char __attribute__((__unused__)) **front_ptr)
{
    char **env_var, **new_environment;
    size_t env_size;
    int idx, idx2;

    if (!arguments[0])
        return write_error(arguments, -1);
    env_var = _getenv(arguments[0]);
    if (!env_var)
        return 0;

    for (env_size = 0; environ[env_size]; env_size++)
        ;

    new_environment = malloc(sizeof(char *) * env_size);
    if (!new_environment)
        return write_error(arguments, -1);

    for (idx = 0, idx2 = 0; environ[idx]; idx++)
    {
        if (*env_var == environ[idx])
        {
            free(*env_var);
            continue;
        }
        new_environment[idx2] = environ[idx];
        idx2++;
    }
    free(environ);
    environ = new_environment;
    environ[env_size - 1] = NULL;

    return 0;
}

/**
 * _copyenv - Creates a copy of the environment variable.
 *
 * Return: NULL, if an error occurs
 *         O/w, a double pointer to the new copy.
 */
char **_copyenv(void)
{
    char **new_environment = NULL;
    size_t env_size = 0;
    int env_index = 0;

    while (environ[env_size] != NULL)
        env_size++;

    new_environment = malloc(sizeof(char *) * (env_size + 1));
    if (!new_environment)
        return NULL;

    for (env_index = 0; environ[env_index] != NULL; env_index++)
    {
        new_environment[env_index] = malloc(_strlen(environ[env_index]) + 1);

        if (!new_environment[env_index])
        {
            while (env_index >= 0)
            {
                free(new_environment[env_index]);
                env_index--;
            }
            free(new_environment);
            return NULL;
        }
        _strcpy(new_environment[env_index], environ[env_index]);
    }
    new_environment[env_index] = NULL;

    return new_environment;
}