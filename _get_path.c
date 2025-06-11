#include "main.h"

/**
 * _get_path - Retrieves the PATH environment variable.
 *
 * Return: A duplicated string of the PATH variable, or NULL if not found.
 * The returned string must be freed by the caller.
 */
char *_get_path(void)
{
	int i = 0;
	char *path_env = NULL;

	while (environ[i] != NULL)
	{
		/* Check if the current environment variable starts with "PATH=" */
		if (strncmp(environ[i], "PATH=", 5) == 0)
		{
			/* Duplicate the string starting after "PATH=" */
			path_env = strdup(environ[i] + 5);
			if (path_env == NULL)
			{
				perror("Error: strdup failed for PATH");
				return (NULL);
			}
			return (path_env);
		}
		i++;
	}
	return (NULL); /* PATH not found in environment */
}

/**
 * _find_command_in_path - Finds a command in the directories listed in PATH.
 * @command: The command name to search for.
 *
 * Return: The full path to the command if found and executable, or NULL otherwise.
 * The returned string must be freed by the caller.
 */
char *_find_command_in_path(char *command)
{
	char *path_copy = NULL;
	char *dir_token;
	char *full_path = NULL;
	char *delim = ":";
	int cmd_len;

	if (command == NULL)
		return (NULL);

	/* If command contains a '/', assume it's a full path already */
	if (strchr(command, '/') != NULL)
	{
		if (access(command, F_OK | X_OK) == 0)
			return (strdup(command));
		return (NULL);
	}

	path_copy = _get_path();
	if (path_copy == NULL)
		return (NULL);

	cmd_len = strlen(command);
	dir_token = strtok(path_copy, delim);

	while (dir_token != NULL)
	{
		/* Allocate space for dir + '/' + command + NULL terminator */
		full_path = malloc(strlen(dir_token) + 1 + cmd_len + 1);
		if (full_path == NULL)
		{
			perror("Error: malloc failed for full_path");
			free(path_copy);
			return (NULL);
		}

		/* Construct full path: directory/command */
		strcpy(full_path, dir_token);
		strcat(full_path, "/");
		strcat(full_path, command);

		/* Check if the constructed path exists and is executable */
		if (access(full_path, F_OK | X_OK) == 0)
		{
			free(path_copy); /* Free the duplicated PATH string */
			return (full_path); /* Return the valid full path */
		}

		free(full_path); /* Free if not found/executable, try next directory */
		full_path = NULL; /* Reset for next iteration */
		dir_token = strtok(NULL, delim);
	}

	free(path_copy); /* Free the duplicated PATH string */
	return (NULL); /* Command not found in any PATH directory */
}
