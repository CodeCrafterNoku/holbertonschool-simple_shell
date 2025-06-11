#include "main.h"

/**
 * _execute_command - Executes a single command after tokenizing.
 * @input_line: The complete command line string from user input.
 *
 * Return: 0 on success, -1 on failure.
 */
int _execute_command(char *input_line)
{
	pid_t pid;
	char *argv[2]; /* Only command name, no arguments */
	char *command_name; /* To store the first token (command) */

	/* Tokenize the input_line to get the actual command name */
	/* Use space, tab, newline as delimiters */
	command_name = strtok(input_line, " \t\n");

	/* If no command is found (e.g., empty line or only spaces), do nothing */
	if (command_name == NULL)
	{
		return (0);
	}

	argv[0] = command_name; /* The first token is argv[0] */
	argv[1] = NULL;         /* Null-terminate the argv array */

	pid = fork(); /* Create a child process */
	if (pid == -1)
	{
		perror("Error: fork failed"); /* Print error if fork fails */
		return (-1);
	}
	else if (pid == 0) /* Child process executes the command */
	{
		/* Attempt to execute the command. If execve fails, print error. */
		if (execve(argv[0], argv, environ) == -1) /* environ is global */
		{
			/* Error message: "./shell: No such file or directory" */
			perror("./shell");
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
