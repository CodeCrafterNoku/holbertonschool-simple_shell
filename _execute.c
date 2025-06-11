#include "main.h"

/**
 * _execute_command - Executes a single command.
 * @command: The command string to execute (full path).
 *
 * Return: 0 on success, -1 on failure.
 */
int _execute_command(char *command)
{
	pid_t pid;
	char *argv[2]; /* Only command name, no arguments */

	argv[0] = command; /* The command itself is argv[0] */
	argv[1] = NULL;    /* Null-terminate the argv array */

	pid = fork(); /* Create a child process */
	if (pid == -1)
	{
		perror("Error: fork failed"); /* Print error if fork fails */
		return (-1);
	}
	else if (pid == 0) /* Child process executes the command */
	{
		/* Attempt to execute the command. If execve fails, print error. */
		if (execve(command, argv, environ) == -1) /* environ is now global */
		{
			/* Error message */
			perror("./shell");
			/*
			 * Use _exit in child to exit immediately without flushing
			 * parent's buffers or running atexit handlers.
			 */
			_exit(EXIT_FAILURE); /* Exit child process on execve failure */
		}
	}
	else /* Parent process waits for the child */
	{
		int status;

		/* Wait for the child process to complete */
		if (waitpid(pid, &status, 0) == -1)
		{
			perror("Error: waitpid failed"); /* Print error if waitpid fails */
			return (-1);
		}
	}
	return (0); /* Command execution handled (child ran or failed, parent waited) */
}
