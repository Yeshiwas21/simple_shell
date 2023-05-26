#include "shell.h"

/**
 * all_alias - Prints all aliases, specific aliases, or sets an alias
 * @arguments: An array of arguments.
 * @front_ptr: A double pointer to the beginning of args.
 *
 * Return: If an error occurs - -1.
 *         Otherwise - 0.
 */
int all_alias(char **arguments, char __attribute__((__unused__)) **front_ptr)
{
    alias_t *temp = aliases;
    int i, return_value = 0;
    char *alias_value;

    if (!arguments[0])
    {
        while (temp)
        {
            print_formatted_alias(temp);
            temp = temp->next;
        }
        return return_value;
    }

    for (i = 0; arguments[i]; i++)
    {
        temp = aliases;
        alias_value = _strchr(arguments[i], '=');
        if (!alias_value)
        {
            while (temp)
            {
                if (_strcmp(arguments[i], temp->alias_name) == 0)
                {
                    print_formatted_alias(temp);
                    break;
                }
                temp = temp->next;
            }
            if (!temp)
                return_value = write_error(arguments + i, 1);
        }
        else
        {
            *alias_value = '\0';
            sets_alias(arguments[i], alias_value);
        }
    }

    return return_value;
}

/**
 * sets_alias - Sets an existing alias 'name' with a new value,
 * 'alias_value' or creates a new alias with 'name' and 'value'.
 * @variable_name: Name of the alias
 * @value: Value of the alias, the 1st character is '='
 */
void sets_alias(char *variable_name, char *alias_value)
{
    alias_t *current_alias = aliases;
    int length, j, k;
    char *new_value;

    *alias_value = '\0';
    alias_value++;

    length = _strlen(alias_value) - _strspn(alias_value, "'\"");

    new_value = malloc(sizeof(char) * (length + 1));
    if (!new_value)
        return;

    for (j = 0, k = 0; alias_value[j]; j++)
    {
        if (alias_value[j] != '\'' && alias_value[j] != '"')
            new_value[k++] = alias_value[j];
    }
    new_value[k] = '\0';

    while (current_alias)
    {
        if (_strcmp(variable_name, current_alias->alias_name) == 0)
        {
            free(current_alias->alias_value);
            current_alias->alias_value = new_value;
            break;
        }
        current_alias = current_alias->next;
    }

    if (!current_alias)
        add_alias_to_end(&aliases, variable_name, new_value);
}

/**
 * replace_aliases - Replace any matching alias with their value
 * @arguments: double pointer to the arguments
 *
 * Return: double pointer to the arguments
 */
char **replace_aliases(char **arguments)
{
    alias_t *current_alias;
    int i = 0;
    char *new_val;

    if (_strcmp(arguments[0], "alias") == 0)
        return arguments;

    while (arguments[i])
    {
        current_alias = aliases;
        while (current_alias)
        {
            if (_strcmp(arguments[i], current_alias->alias_name) == 0)
            {
                new_val = malloc(sizeof(char) * (_strlen(current_alias->alias_value) + 1));
                if (!new_val)
                {
                    free_arguments(arguments, arguments);
                    return NULL;
                }
                _strcpy(new_val, current_alias->alias_value);

                free(arguments[i]);
                arguments[i] = new_val;
                i--;
                break;
            }
            current_alias = current_alias->next;
        }
        i++;
    }

    return arguments;
}

/**
 * print_formatted_alias - Prints the alias in the format name='value'.
 * @current_alias: Pointer to the current alias
 */
void print_formatted_alias(alias_t *current_alias)
{
    char *alias_str;
    int length = _strlen(current_alias->alias_name) + _strlen(current_alias->alias_value) + 4;

    alias_str = malloc(sizeof(char) * (length + 1));
    if (!alias_str)
        return;
    _strcpy(alias_str, current_alias->alias_name);
    _strcat(alias_str, "='");
    _strcat(alias_str, current_alias->alias_value);
    _strcat(alias_str, "'\n");

    write(STDOUT_FILENO, alias_str, length);
    free(alias_str);
}