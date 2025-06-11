#include "main.h"

/**
 * handle_sigint - Signal handler for SIGINT (Ctrl+C).
 * @sig: The signal number.
 *
 * This function handles the Ctrl+C signal by printing a new line and
 * redisplaying the shell prompt.
 */
void handle_sigint(int sig)
{
	(void)sig; /* Cast to void to suppress unused parameter warning */
	printf("\n"); /* Print a new line */
	printf("$ "); /* Print the shell prompt */
	fflush(stdout); /* Ensure prompt is displayed immediately */
}

/**
 * main - Entry point for the simple shell.
 *
 * This function implements the main loop of the shell, handling prompt
 * display, command input, execution, and basic error conditions.
 *
 * Return: The exit status of the last executed command,
 * or EXIT_SUCCESS on EOF, or EXIT_FAILURE on critical error.
 */
int main(void)
{
	char *line = NULL; /* Buffer to store the command line */
	size_t len = 0;    /* Size of the allocated buffer */
	ssize_t read_bytes; /* Number of bytes read by getline */
	int last_command_status = 0; /* Store the exit status of the last command */

	/* Set up signal handler for SIGINT (Ctrl+C) */
	if (signal(SIGINT, handle_sigint) == SIG_ERR)
	{
		perror("Error: Cannot set signal handler");
		return (EXIT_FAILURE);
	}

	/* Main shell loop */
	while (1) /* Loop indefinitely until explicit exit or EOF */
	{
		read_bytes = _read_command_line(&line, &len);
		if (read_bytes == -1)
		{
			/* For EOF, exit with the last command's status */
			break; /* Exit shell loop on EOF or getline error */
		}

		/* Remove trailing newline character from the input */
		if (read_bytes > 0 && line[read_bytes - 1] == '\n')
		{
			line[read_bytes - 1] = '\0';
		}

		/* Execute the command and store its exit status */
		last_command_status = _execute_command(line);
	}

	free(line); /* Free the dynamically allocated buffer by getline */
	/* Return the status of the last command executed or 0 for successful EOF */
	return (last_command_status);
}
