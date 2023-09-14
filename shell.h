#ifndef SHELL_H
#define SHELL_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <errno.h>
#include <fcntl.h>


#define DELIM " \t\n"
extern char **environ;

char *read_cmd(void);
char **tokenizer(char line);
int _execute(char **command, char **argv);

char *_strcat(char *dest, char *src);
char *_strcpy(char *dest, char *src);
char *_strdup (const char *str);
int_strcmp(char *51, char *s2);
int_strlen(char *s);

void free2darray(char **arr);

#endif