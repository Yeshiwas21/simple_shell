#ifndef _SHELL_H_
#define _SHELL_H_

#include <fcntl.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <stdio.h>

#define END_OF_FILE -2
#define EXIT -3

/* Global environemnt */
extern char **environ;
/* Global program name */
char *name;
/* Global history counter */
int hist;

/**
 * struct list_s - A new struct type defining a linked list.
 * @dir: A directory path.
 * @next: A pointer to another struct list_s.
 */
typedef struct list_s
{
	char *dir_path;
	struct list_s *next;
} list_t;

/**
 * struct builtin_s - A new struct type defining builtin commands.
 * @name: The name of the builtin command.
 * @f: A function pointer to the builtin command's function.
 */
typedef struct builtin_s
{
	char *name;
	int (*f)(char **argv, char **front);
} builtin_t;

/**
 * struct alias_s - A new struct defining aliases.
 * @name: The name of the alias.
 * @value: The value of the alias.
 * @next: A pointer to another struct alias_s.
 */
typedef struct alias_s
{
	char *alias_name;
	char *alias_value;
	struct alias_s *next;
} alias_t;

/* Global aliases linked list */
alias_t *aliases;

/* Main Helpers */
void reassign_lineptr(char **lineptr, size_t *n, char *buffer, size_t bufferSize);
ssize_t read_input(char **lineptr, size_t *size, FILE *stream);
void *mem_realloc(void *ptr, unsigned int old_size, unsigned int new_size);
char **token_strtok(char *line, char *delim_char);
char *get_command_location(char *command);
list_t *get_dir_path(char *dir_list);
char *fill_dir_path(char *dir_path);
int executeCustomCommand(char **arguments, char **front_ptr);
void free_list(list_t *head);
char *_itoa(int num);
void handle_signal(int signal_number);

/* alias */
int all_alias(char **arguments, char __attribute__((__unused__)) **front_ptr);
void print_formatted_alias(alias_t *current_alias);
void sets_alias(char *variable_name, char *value);

/* Builtins */
ssize_t read_input(char **input_buff, size_t *size, FILE *strm);
int (*get_command(char *command))(char **arguments, char **front_ptr);
int change_dir(char **arguments, char __attribute__((__unused__)) **front_ptr);
int exit_shell(char **arguments, char **front_ptr);
int shell_help(char **arguments, char __attribute__((__unused__)) **front_ptr);

/* enviroment */
int print_env(char **arguments, char __attribute__((__unused__)) **front_ptr);
int _setenv(char **arguments, char __attribute__((__unused__)) **front_ptr);
int _unsetenv(char **arguments, char __attribute__((__unused__)) **front_ptr);
char *gets_env_value(char *beginning, int length);
char **_copyenv(void);
void frees_env(void);
char **_getenv(const char *var_name);

/* Error Handling */
int write_error(char **arguments, int error_val);
char *error_for_env(char **arguments);
char *error_1_alias(char **arguments);
char *error_for_exit(char **arguments);
char *error_for_cd(char **arguments);
char *error_for_syntax(char **arguments);
char *error_for_126(char **arguments);
char *error_for_127(char **arguments);

/* File */
int open_erro(char *file_path);
int run_file_commands(char *file_path, int *exe_ret);

/* Input Helpers */
char *retrieve_arguments(char *input_command, int *execution_return);
int calls_arguments(char **arguments, char **front_ptr, int *execution_return);
int runs_arguments(char **arguments, char **front_ptr, int *execution_return);
int handles_arguments(int *execution_return);
int checks_arguments(char **arguments);
void handles_line(char **line_read, ssize_t read_length);
char *get_env_value(char *env_var, int env_length);
void free_arguments(char **arguments, char **front_ptr);
void replace_var(char **arguments, int *execution_return);
char *get_current_pid(void);
char **replace_aliases(char **args);
ssize_t get_new_length(char *line);
void update_logical_ops(char *line, ssize_t *new_length);
int token_length(char *string, char *delim_char);


/* Linkedlist Helpers */
alias_t *add_alias_to_end(alias_t **head_ptr, char *alias_name, char *alias_value);
list_t *add_node_to_end(list_t **head_ptr, char *dir_path);
void frees_alias_list(alias_t *head_ptr);
void frees_list(list_t *head_ptr);

void help_for_all(void);
void help_alias(void);
void help_for_cd(void);
void help_for_exit(void);
void help_for_alias(void);
void help_for_help(void);


/* Displays Help */
void help_all_env(void);
void help_set_env(void);
void help_unset_env(void);
void help_history(void);
/* String functions */
int _strlen(const char *s);
char *_strcat(char *dest, const char *src);
char *_strncat(char *dest, const char *src, size_t n);
char *_strcpy(char *dest, const char *src);
char *_strchr(char *s, char c);
int _strspn(char *s, char *accept);
int _strcmp(char *s1, char *s2);
int _strncmp(const char *s1, const char *s2, size_t n);


#endif /* _SHELL_H_ */
