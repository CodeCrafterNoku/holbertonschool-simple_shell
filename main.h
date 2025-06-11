#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>    /* For printf, perror, getline, stdin */
#include <stdlib.h>   /* For EXIT_SUCCESS, EXIT_FAILURE, malloc, free */
#include <unistd.h>   /* For execve, fork, wait, _exit, fflush, isatty, access, F_OK, X_OK */
#include <sys/types.h>/* For pid_t */
#include <sys/wait.h> /* For waitpid */
#include <string.h>   /* For strcmp, strcspn, strlen, strtok, strdup */
#include <signal.h>   /* For signal, SIGINT */

/* Global environment variable, declared extern here */
extern char **environ;

/* Prototypes */
void handle_sigint(int sig);
/* _execute_command now returns a special code for 'exit' built-in */
int _execute_command(char *command);
/**
 * _read_command_line - Reads a line from stdin and handles EOF/errors.
 * @line: A pointer to the buffer storing the command line.
 * @len: A pointer to the size of the allocated buffer.
 *
 * Return: Number of bytes read on success, -1 on EOF or error.
 */
ssize_t _read_command_line(char **line, size_t *len);

/* New Prototypes for PATH handling */
char *_get_path(void);
char *_find_command_in_path(char *command);

#endif /* MAIN_H */
