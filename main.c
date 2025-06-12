#include "main.h"

void print_prompt(void)
{
    printf("#cisfun$ ");
}

int main(void)
{
    char *line = NULL;
    size_t len = 0;
    ssize_t read_bytes;
    int last_command_status = 0;

    while (1)
    {
        print_prompt();
        read_bytes = _read_command_line(&line, &len);
        
        if (read_bytes == -1)
        {
            if (isatty(STDIN_FILENO))
                printf("\n");
            break;
        }

        if (read_bytes == 0)
            continue;

        last_command_status = _execute_command(line);
    }

    free(line);
    return last_command_status;
}
