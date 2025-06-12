#include "main.h"

ssize_t _read_command_line(char **line, size_t *len)
{
    return getline(line, len, stdin);
}

int _execute_command(char *line)
{
    pid_t pid;
    int status;
    char *args[2];

    line[strcspn(line, "\n")] = 0; /* Remove newline */

    if (strlen(line) == 0)
        return 0;

    if (strcmp(line, "exit") == 0)
        exit(0);

    if (strcmp(line, "env") == 0)
    {
        char **env = environ;
        while (*env)
            printf("%s\n", *env++);
        return 0;
    }

    args[0] = line;
    args[1] = NULL;

    pid = fork();
    if (pid == 0) /* Child process */
    {
        char *command_full_path = _find_command_in_path(args[0]);
        if (command_full_path == NULL)
        {
            perror("./hsh");
            exit(127);
        }
        execve(command_full_path, args, environ);
        perror("./hsh");
        exit(127);
    }
    else if (pid < 0) /* Fork error */
    {
        perror("fork");
        return -1;
    }
    else /* Parent process */
    {
        wait(&status);
        return WIFEXITED(status) ? WEXITSTATUS(status) : -1;
    }
}
