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

	/* Only print prompt if in interactive mode */
	if (isatty(STDIN_FILENO))
	{
		printf("$ ");
		fflush(stdout); /* Ensure prompt is displayed immediately */
	}

	/* Read a line from standard input */
	read_bytes = getline(line, len, stdin);

	/* If getline returns -1, it's either EOF or an error. Exit. */
	if (read_bytes == -1)
	{
		/* No specific error message needed for EOF */
		return (-1);
	}
	return (read_bytes);
}
