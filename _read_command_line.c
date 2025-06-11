#include "main.h"

/**
 * _read_command_line - Reads a line from stdin and handles EOF/errors.
 * @line: A pointer to the buffer storing the command line.
 * @len: A pointer to the size of the allocated buffer.
 *
 * Return: Number of bytes read on success, -1 on EOF or error.
 */
ssize_t _read_command_line(char **line, size_t *len)
{
	ssize_t read_bytes;

	printf("$ "); /* Display the shell prompt */
	fflush(stdout); /* Ensure prompt is displayed immediately */

	/* Read a line from standard input */
	read_bytes = getline(line, len, stdin);

	/* Check for EOF (Ctrl+D) or other getline errors */
	if (read_bytes == -1)
	{
		if (feof(stdin)) /* Check if it's genuinely EOF */
		{
			printf("\n"); /* Print a newline before exiting on EOF */
		}
		else
		{
			perror("Error: getline failed"); /* Print error for other failures */
		}
	}
	return (read_bytes);
}
