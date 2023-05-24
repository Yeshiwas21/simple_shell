#ifndef SHELL_H
#define SHELL_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <limits.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <stddef.h>

#define BUFFER_SIZE 1024
extern char **environ;
int _strlen(char *s);
char *_strcpy(char *dest, char *src);
int _strcmp(char *s1, char *s2);
char *get_cmdpath(char *cmd);
char *get_env(void);
int _strncmp(char *s1, char *s2, int n);
char  *_strcat(char *dest, char *src);
void print_env(char **env);
void *get_line(void);
int _putchar(char c);
void free_memory_pp(void **ptr);
void free_memory_p(void *ptr);

#endif
