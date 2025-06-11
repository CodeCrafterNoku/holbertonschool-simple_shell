#include <stdio.h> /* For printf, fgets, stdout */
#include <stdlib.h> /* For EXIT_SUCCESS */
#include <string.h> /* For strlen, strcspn */

/**
 * main - Entry point for the simple shell.
 *
 * Return: Always EXIT_SUCCESS on successful execution.
 */
int main(void)
{
	char *line = NULL;
	size_t len = 0;
	ssize_t read;

	while (1) /* Infinite loop for shell prompt */
	{
		printf("$ "); /* Print prompt */

		/* Read a line from stdin */
		read = getline(&line, &len, stdin);
		if (read == -1) /* Handle EOF (Ctrl+D) or error */
		{
			printf("\nExiting shell.\n");
			break; /* Exit loop */
		}

		/* Remove newline character if present */
		if (line[read - 1] == '\n')
		{
			line[read - 1] = '\0';
		}

		/* Example: simple exit command */
		if (strcmp(line, "exit") == 0)
		{
			printf("Exiting shell.\n");
			break; /* Exit loop */
		}

		/* In a real shell, you would parse and execute 'line' here */
		printf("You typed: %s\n", line);
	}

	free(line); /* Free allocated memory for line buffer */
	return (EXIT_SUCCESS);
}
