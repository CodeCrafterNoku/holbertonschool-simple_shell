#include "main.h"

#define SHELL_EXIT_CODE 999 /* Special code for 'exit' built-in */

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
 * Return: The exit status of the shell, based on the last command executed
 * or specific built-in actions.
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
			/* On EOF or getline error, exit with last known status or 0 if none */
			break; /* Exit shell loop */
		}

		/* Remove trailing newline character from the input */
		if (read_bytes > 0 && line[read_bytes - 1] == '\n')
		{
			line[read_bytes - 1] = '\0';
		}

		/* Execute the command and store its exit status */
		last_command_status = _execute_command(line);

		/* If _execute_command returned SHELL_EXIT_CODE, then exit */
		if (last_command_status == SHELL_EXIT_CODE)
		{
			last_command_status = EXIT_SUCCESS; /* For 'exit' built-in, return 0 status */
			break; /* Exit loop to free line and terminate */
		}
	}

	free(line); /* Free the dynamically allocated buffer by getline */
	return (last_command_status); /* Return the stored status as shell's exit status */
}
