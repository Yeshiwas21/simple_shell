#ifndef _SHELL_H_
#define _SHELL_H_

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <limits.h>
#include <fcntl.h>
#include <errno.h>

/* for read/write buffers */
#define READ_BUF_SIZE 1024
#define WRITE_BUF_SIZE 1024
#define BUF_FLUSH -1

/* for command chaining */
#define CMD_NORM	0
#define CMD_OR		1
#define CMD_AND		2
#define CMD_CHAIN	3

/* for convert_number() */
#define CONVERT_LOWERCASE	1
#define CONVERT_UNSIGNED	2

/* 1 if using system getline() */
#define USE_GETLINE 0
#define USE_STRTOK 0

#define HIST_FILE	".simple_shell_history"
#define HIST_MAX	4096

extern char **environ;


/**
 * struct liststr - singly linked list
 * @num: the number field
 * @str: a string
 * @next: points to the next node
 */
typedef struct liststr
{
	int num;
	char *str;
	struct liststr *next;
} list_t;

/**
 *struct passinfo - contains pseudo-arguements to pass into a function,
 *		allowing uniform prototype for function pointer struct
 *@arg: a string generated from getline containing arguements
 *@argv: an array of strings generated from arg
 *@path: a string path for the current command
 *@argc: the argument count
 *@line_count: the error count
 *@err_num: the error code for exit()s
 *@linecount_flag: if on count this line of input
 *@fname: the program filename
 *@env: linked list local copy of environ
 *@environ: custom modified copy of environ from LL env
 *@history: the history node
 *@alias: the alias node
 *@env_changed: on if environ was changed
 *@status: the return status of the last exec'd command
 *@cmd_buf: address of pointer to cmd_buf, on if chaining
 *@cmd_buf_type: CMD_type ||, &&, ;
 *@readfd: the fd from which to read line input
 *@histcount: the history line number count
 */
typedef struct passinfo
{
	char *arg;
	char **argv;
	char *path;
	int argc;
	unsigned int line_count;
	int err_num;
	int linecount_flag;
	char *fname;
	list_t *env;
	list_t *history;
	list_t *alias;
	char **environ;
	int env_changed;
	int status;

	char **cmd_buf; /* pointer to cmd ; chain buffer, for memory mangement */
	int cmd_buf_type; /* CMD_type ||, &&, ; */
	int readfd;
	int histcount;
} info_t;

#define INFO_INIT \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
	0, 0, 0}

/**
 *struct builtin - contains a builtin string and related function
 *@type: the builtin command flag
 *@func: the function
 */
typedef struct builtin
{
	char *type;
	int (*func)(info_t *);
} builtin_table;


/* toem_shloop.c */
int hsh(info_t *info, char **av);
int find_builtin(info_t *info);
void find_cmd(info_t *info);
void fork_cmd(info_t *info);

/* toem_parser.c */
int is_cmd(info_t *info, char *path);
char *dup_chars(char *path_str, int start, int stop);
char *find_path(info_t *info, char *path_str, char *cmd);

/* loophsh.c */
int loophsh(char **);

/* toem_errors.c */
void _eputs(char *str);
int _eputchar(char chr)
int _putfd(char chr, int file_desc);
int _putsfd(char *str, int file_desc);

/* toem_string.c */
int _strlen(char *str);
int _strcmp(char *str1, char *str2);
char *starts_with(const char *haystack, const char *needle);
char *_strcat(char *dest, char *src);

/* toem_string1.c */
char *_strcpy(char *dest, char *src);
char *_strdup(const char *str);
void _puts(char *str);
int _putchar(char chr);

/* toem_exits.c */
char *_strncpy(char *dest, char *src, int n)
char *_strncat(char *dest, char *src, int n);
char *_strchr(char *str, char chr);

/* toem_tokenizer.c */
char **strtow(char *str, char *delim);
char **strtow2(char *str, char delim);

/* toem_realloc.c */
char *_memset(char *s, char b, unsigned int n);
void ffree(char **ss);
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size);

/* toem_memory.c */
int bfree(void **ptr);

/* toem_atoi.c */
int interactive_mode(info_t *);
int is_delim(char chr, char *delim);
int _isalpha(int chr);
int _atoi(char *str);

/* toem_errors1.c */
int _erratoi(char *str);
void print_error(info_t *info, char *estr);
int print_d(int input, int file_desc);
char *convert_number(long int num, int base, int flags);
void remove_comments(char *buff);

/* toem_builtin.c */
int shell_exit(info_t *info);
int shell_cd(info_t *info);
int shell_help(info_t *info);

/* toem_builtin1.c */
int shell_history(info_t *info);
int shell_alias(info_t *info);

/*toem_getline.c */
ssize_t input_buf(info_t *info, char **buf, size_t *len);
ssize_t get_input(info_t *info);
ssize_t read_buf(info_t *info, char *buf, size_t *i);
int _getline(info_t *info, char **ptr, size_t *length);
void sigintHandler(int);

/* toem_getinfo.c */
void clear_info(info_t *info);
void set_info(info_t *info, char **av);
void free_info(info_t *info, int all);

/* toem_environ.c */
int shell_env(info_t *info);
char *_getenv(info_t *info, const char *name);
int shell_setenv(info_t *info);
int shell_unsetenv(info_t *info);
int populate_env_list(info_t *info);

/* toem_getenv.c */
char **get_environ(info_t *info);
int _unsetenv(info_t *info, char *env_var);
int _setenv(info_t *info, char *env_var, char *value);

/* toem_history.c */
char *get_history_file(info_t *info);
int write_history(info_t *info);
int read_history(info_t *info);
int build_history_list(info_t *info, char *buff, int linecount);
int renumber_history(info_t *info);

/* toem_lists.c */
list_t *add_node(list_t **head, const char *str, int num);
list_t *add_node_end(list_t **head, const char *str, int num);
size_t print_list_str(const list_t *first_node);
int delete_node_at_index(list_t **head, unsigned int index);
void free_list(list_t **head_ptr);

/* toem_lists1.c */
size_t list_len(const list_t *first_node);
char **list_to_strings(list_t *head);
size_t print_list(const list_t *first_node);
list_t *node_starts_with(list_t *node, char *prefix, char chr);
ssize_t get_node_index(list_t *head, list_t *node)

/* toem_vars.c */
int is_chain(info_t *info, char *buf, size_t *p);
void check_chain(info_t *info, char *buff, size_t *p, size_t index, size_t len);
int replace_alias(info_t *info);
int replace_vars(info_t *info);
int replace_string(char **old_str, char *new_str);

#endif
