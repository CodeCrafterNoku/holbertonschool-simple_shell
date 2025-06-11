#include "main.h"

#define MAX_ARGS 64 /* Maximum number of arguments + command + NULL */

/**
 * _execute_command - Executes a command with arguments.
 * @input_line: The complete command line string from user input.
 *
 * Return: The exit status of the command, or 127 if command not found.
 * Returns -1 for internal shell errors (fork/waitpid failure).
 */
int _execute_command(char *input_line)
{
	pid_t pid;
	char *argv[MAX_ARGS]; /* Array to hold command and arguments */
	char *token;
	int i = 0;
	char *command_full_path = NULL; /* To store the full path of the command */
	int status = 0; /* To store child process status */

	/* Get the first token (command) */
	token = strtok(input_line, " \t\n");
	if (token == NULL) /* Handle empty line or spaces-only line */
	{
		return (0); /* Return 0 for empty command */
	}

	/* Build the argv array by getting subsequent tokens */
	while (token != NULL && i < MAX_ARGS - 1)
	{
		argv[i] = token;
		token = strtok(NULL, " \t\n");
		i++;
	}
	argv[i] = NULL; /* Null-terminate the argv array */

	/* Attempt to find the command's full path */
	command_full_path = _find_command_in_path(argv[0]);

	if (command_full_path == NULL) /* Command not found or not executable */
	{
		/* Print error message: "./hsh: 1: ls: not found" */
		fprintf(stderr, "./hsh: 1: %s: not found\n", argv[0]);
		return (127); /* Return 127 for command not found */
	}

	/* If command found, then fork */
	pid = fork();
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
			perror("./hsh"); /* Use ./hsh as program name for execve error */
			free(command_full_path); /* Free path before exiting child */
			_exit(127); /* Exit child with 127 for execve failure */
		}
	}
	else /* Parent process waits for the child */
	{
		free(command_full_path); /* Free path in parent after fork */
		if (waitpid(pid, &status, 0) == -1)
		{
			perror("Error: waitpid failed");
			return (-1); /* Indicate shell internal error */
		}
		if (WIFEXITED(status)) /* Check if child exited normally */
		{
			return (WEXITSTATUS(status)); /* Return child's exit status */
		}
	}
	return (0); /* Default return for parent if child didn't exit normally (e.g., signal) */
}
