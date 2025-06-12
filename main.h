#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>

#define MAX_COMMAND_LENGTH 1024

extern char **environ;

/* Function prototypes */
ssize_t _read_command_line(char **line, size_t *len);
int _execute_command(char *line);
void print_prompt(void);
char *_find_command_in_path(char *command);

#endif /* MAIN_H */
