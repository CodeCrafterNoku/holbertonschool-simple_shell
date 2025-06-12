#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>

#define MAX_COMMAND_LENGTH 100

extern char **environ;

int main(void)
{
    char command[MAX_COMMAND_LENGTH];
    pid_t pid;
    int status;
    
    while (1)
    {
        printf("#cisfun$ ");
        if (fgets(command, MAX_COMMAND_LENGTH, stdin) == NULL)
            break;  // Handle Ctrl+D
        
        // Remove newline character
        command[strcspn(command, "\n")] = 0;
        
        if (strlen(command) == 0)
            continue;
        
        pid = fork();
        if (pid == 0)
        {
            // Child process
            char *args[] = {command, NULL};
            if (execve(command, args, environ) == -1)
            {
                perror("./shell");
                exit(EXIT_FAILURE);
            }
        }
        else if (pid < 0)
        {
            perror("fork");
        }
        else
        {
            // Parent process
            wait(&status);
        }
    }
    
    printf("\n");
    return EXIT_SUCCESS;
}
