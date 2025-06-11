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
	char *command_full_path = NULL; /* To store the full path of the command */

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

	/* Find the full path of the command using PATH environment variable */
	command_full_path = _find_command_in_path(argv[0]);

	if (command_full_path == NULL) /* Command not found or not executable */
	{
		/* Print error message */
		perror("./shell");
		return (-1);
	}

	pid = fork(); /* Create a child process */
	if (pid == -1)
	{
		perror("Error: fork failed");
		free(command_full_path); /* Free path before returning */
		return (-1);
	}
	else if (pid == 0) /* Child process executes the command */
	{
		/* Attempt to execute the command with full argv array. */
		if (execve(command_full_path, argv, environ) == -1)
		{
			/* Error message (should ideally not happen if _find_command_in_path worked) */
			perror("./shell");
			free(command_full_path); /* Free path before exiting child */
			_exit(EXIT_FAILURE); /* Exit child process on execve failure */
		}
	}
	else /* Parent process waits for the child */
	{
		int status;

		free(command_full_path); /* Free path in parent after fork */
		if (waitpid(pid, &status, 0) == -1)
		{
			perror("Error: waitpid failed");
			return (-1);
		}
	}
	return (0);
}
