#include "main.h"

#define MAX_ARGS 64 /* Maximum number of arguments + command + NULL */

/**
 * _execute_command - Executes a command with arguments.
 * @input_line: The complete command line string from user input.
 *
 * Return: 0 on success, -1 on failure.
 */
int _execute_command(char *input_line)
{
	pid_t pid;
	char *argv[MAX_ARGS]; /* Array to hold command and arguments */
	char *token;
	int i = 0;

	/* Get the first token (command) */
	token = strtok(input_line, " \t\n");
	if (token == NULL) /* Handle empty line or spaces-only line */
	{
		return (0);
	}

	/* Build the argv array by getting subsequent tokens */
	while (token != NULL && i < MAX_ARGS - 1)
	{
		argv[i] = token;
		token = strtok(NULL, " \t\n");
		i++;
	}
	argv[i] = NULL; /* Null-terminate the argv array */

	pid = fork(); /* Create a child process */
	if (pid == -1)
	{
		perror("Error: fork failed");
		return (-1);
	}
	else if (pid == 0) /* Child process executes the command */
	{
		/* Attempt to execute the command with full argv array. */
		if (execve(argv[0], argv, environ) == -1)
		{
			/* Error message: "./shell: No such file or directory" */
			perror("./shell");
			_exit(EXIT_FAILURE); /* Exit child process on execve failure */
		}
	}
	else /* Parent process waits for the child */
	{
		int status;

		if (waitpid(pid, &status, 0) == -1)
		{
			perror("Error: waitpid failed");
			return (-1);
		}
	}
	return (0);
}
