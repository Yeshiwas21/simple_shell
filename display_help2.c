#include "shell.h"

/**
 * help_all_env - Displays information on the shellby builtin command 'env'.
 */
void help_all_env(void)
{
    char *msg = "env: env\n"
                "\tPrints the current environment.\n";

    write(STDOUT_FILENO, msg, _strlen(msg));
}

/**
 * help_setenv - Displays information on the shellby builtin command 'setenv'.
 */
void help_set_env(void)
{
    char *msg = "setenv: setenv [VARIABLE] [VALUE]\n"
                "\tInitializes a new environment variable, or modifies an existing one.\n\n"
                "\tUpon failure, prints a message to stderr.\n";

    write(STDOUT_FILENO, msg, _strlen(msg));
}
/**
 * help_unsetenv - Displays information on the shellby builtin command
 * 'unsetenv'.
 */
void help_unset_env(void)
{
    char *msg = "unsetenv: unsetenv [VARIABLE]\n"
                "\tRemoves an environmental variable.\n\n"
                "\tUpon failure, prints a message to stderr.\n";

    write(STDOUT_FILENO, msg, _strlen(msg));
}