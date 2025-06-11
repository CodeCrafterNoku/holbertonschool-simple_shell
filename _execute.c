#include "main.h"

#define MAX_ARGS 64 /* Maximum number of arguments + command + NULL */
#define SHELL_EXIT_CODE 999 /* Special code for 'exit' built-in */

/**
 * _execute_command - Executes a command with arguments or handles built-ins.
 * @input_line: The complete command line string from user input.
 *
 * Return: The exit status of the command. Returns 127 if command not found.
 * Returns -1 for internal shell errors (fork/waitpid failure).
 * Returns SHELL_EXIT_CODE if 'exit' built-in is called.
 * Returns 0 for empty commands or successful built-ins.
 */
int _execute_command(char *input_line)
{
	pid_t pid;
	char *argv[MAX_ARGS]; /* Array to hold command and arguments */
	char *token;
	int i = 0;
	char *command_full_path = NULL;
	int status;
	int env_idx = 0; /* Index for iterating through environ */

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

	/* --- Handle Built-in Commands --- */
	if (strcmp(argv[0], "exit") == 0)
	{
		return (SHELL_EXIT_CODE); /* Return special code for 'exit' */
	}
	else if (strcmp(argv[0], "env") == 0)
	{
		env_idx = 0;
		while (environ[env_idx] != NULL)
		{
			printf("%s\n", environ[env_idx]);
			env_idx++;
		}
		return (0); /* env built-in always exits with 0 on success */
	}
	/* --- End Built-in Commands --- */

	/* Attempt to find the command's full path */
	command_full_path = _find_command_in_path(argv[0]);

	if (command_full_path == NULL) /* Command not found or not executable */
	{
		fprintf(stderr, "./hsh: 1: %s: not found\n", argv[0]);
		return (127); /* Return 127 for command not found */
	}

	/* If command found, then fork */
	pid = fork();
	if (pid == -1)
	{
		perror("Error: fork failed");
		free(command_full_path);
		return (-1); /* Shell internal error */
	}
	else if (pid == 0) /* Child process executes the command */
	{
		if (execve(command_full_path, argv, environ) == -1)
		{
			perror("./hsh");
			free(command_full_path);
			_exit(127); /* Child exits with 127 for execve failure */
		}
	}
	else /* Parent process waits for the child */
	{
		free(command_full_path);
		if (waitpid(pid, &status, 0) == -1)
		{
			perror("Error: waitpid failed");
			return (-1); /* Shell internal error */
		}
		/* Propagate child's exit status */
		if (WIFEXITED(status))
		{
			return (WEXITSTATUS(status));
		}
		/* If child was terminated by a signal (WIFSIGNALED) or stopped (WIFSTOPPED) */
		return (1); /* General failure for non-normal exit */
	}
	return (0); /* Should ideally not be reached, but as a fallback */
}
